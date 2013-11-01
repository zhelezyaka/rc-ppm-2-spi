/*
 This project is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 IT is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Deviation.  If not, see <http://www.gnu.org/licenses/>.
 
 This file is the work of and copyright Cameron Weeks <th9xer@gmail.com>
 http://code.google.com/p/rc-ppm-2-spi/
 
 Thanks to Kilrah for the Spektrum channel order implimentation

 */
 
#include "common.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h> 

#define NEUTRAL 0

//We have 7 modes and a servo travel of 20000 (+-10000) 
//20000/7 = 2857 
#define MODE_DIVISOR 2858 

// ******************************************************************************************
// ******                        Global Variables                                      ******
// ******************************************************************************************

volatile uint8_t g_servo_count = 0;
volatile uint8_t g_sync_count = 0;
volatile uint16_t g_icr1_previous = 0;
volatile uint8_t g_initializing = 1;
volatile uint8_t g_need_to_sync = 1;
volatile uint16_t g_entropy = 0;
uint8_t proto_mode;
struct Transmitter Transmitter;
struct Model Model;
volatile s16 Channels[NUM_OUT_CHANNELS];
volatile uint8_t g_spektrum_order = 0;

s16 chtemp;
int main (void)
{
int16_t i;
uint8_t j;
uint8_t mcusr_mirror;

//The correct sequence of events to disable the watchdog timer
mcusr_mirror = MCUSR;
MCUSR = 0;
wdt_disable();

Model.num_channels = 8;
Model.tx_power = TXPOWER_100mW ;
g_entropy=0;

PORTB=0;
gpio_clear (DDRB, PPM_IN);  // Input  pin0
gpio_set   (DDRB, DEBUG_1); // Output pin1
gpio_set   (DDRB, DEBUG_2); // Output pin2 (SS output - General purpose output pin)
gpio_set   (DDRB,3);        // MOSI output 
gpio_clear (DDRB,4);        // MISO input
gpio_set   (DDRB,5);        // SCK output

PORTC=0;
gpio_set   (DDRC, SPI_CS);   // Output pin3
gpio_clear (DDRC, CH_ORD);   // Input pin4
gpio_set   (PORTC,CH_ORD);   // Pull up resistor on pin4
gpio_clear (DDRC, BIND_SW);  // Input pin5
gpio_set   (PORTC,BIND_SW);  // Pull up resistor on pin5


PORTD=0;
gpio_clear (DDRD, 0);  // Serial Rx input
gpio_set   (DDRD, 1);  // Serial Tx output
gpio_set   (DDRD, LED_G);  // LED green  pin2
gpio_set   (DDRD, LED_R);  // LED red    pin3
gpio_set   (DDRD, LED_Y);  // LED yellow pin4
gpio_set   (DDRD, LED_O);  // LED orange pin5


/* Bit bang SPI, to delete
// SPI INIT Bidirectional one wire mode, set to output
DATA_BI_OUT();
DATA_BI_LO();
DATA_PD_LOW();
CLK_OUT();
CLK_LO();
CS_OUT();
CS_HI();
*/


// SPI Setup
//No interrupts SPIE=0 , SPI Enable SPE=1, MSB first DORD=0, Master mode MSTR =1
//Clock polarity, idle low CPOL=0, Sample leading edge CPHA=0, fosc/2 SPR1=0 SPR0=0 SPI2X=1
//Thanks Rick for the tip that fosc/2 worked ok !
SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
SPSR |= (1<<SPI2X);

// Set up for input capture on PD6
// Normal mode, OVF @ TOP (0xFFFF), F_CPU/8, noice cancler on ICP, falling edge trigger
// 2Mhz Tick
TCCR1B = (1<<ICNC1) | (2<<CS10); // falling edge trigger 
//TCCR1B = (1<<ICNC1) | (2<<CS10) | (1<<ICES1); //rising edge trigger

// Enable ICP interrupt
TIMSK1 = (1<<ICIE1); 
// Global interrupt enable
sei();

//Wait until we have received 20 PPM packets.
//Gives tx output time to start.
while (g_sync_count <= 20) ;   

// Disable Input Capture
TCCR1B &= ~(1<<ICNC1);

// Get some much needed entropy for rand()
srand(g_entropy); 

// Check to see if a tx id has been generated before
if (eeprom_read_byte((uint8_t*)0x05) == eeprom_read_byte((uint8_t*)0x06))
	{
	Model.fixed_id = rand() + ((u32)rand() << 16);
	eeprom_write_dword ((uint32_t*)0x00,Model.fixed_id);
	eeprom_write_byte ((uint8_t*)5,0x34); //Just two different numbers to denote a locked in tx id
	eeprom_write_byte ((uint8_t*)6,0xA4);
	}
else
	{
	Model.fixed_id = eeprom_read_dword((uint32_t*)0x00);
	}

// There is a possible bug in the FlySky protocol code (flysky_a7105.c). 
// Thanks Rick for spotting this, you know who you are !
//
// To set the picture:
// to obtain the channel number chanoffset is subtracted from a number in tx_channels[]
// The code in flysky_a7105.c is:
// A7105_WriteData(packet, 21, tx_channels[chanrow][chancol]-chanoffset);
//
// The chanoffset variable which is some number between 0-15 (and as it is solely based 
// on tx id could well be any of these numbers) is going to cause a negative channel 
// number (or wrap around, whatever you want to call it) at some point because the 
// lowest channel number in tx_channels[] is 10.
//
// chanoffset is (bits 4-7 of tx id) and is controllable independently from 
// chanrow (bits 0-3 of tx id) and chancol (rolling 0-15), so this is 
// guaranteed to happen given the right tx id.
//
// Therefore we must constrain bits 4-7 of tx id to 0-9 to be safe

if (((Model.fixed_id & 0xff) / 16) > 9 ) 
	{
	Model.fixed_id &= 0xffffff0f;
	Model.fixed_id |= 0x00000090;
	}

//Channel 8 tells us what mode to be in
chtemp = Channels[7];
for (i=(-10000+MODE_DIVISOR), j=0; i<chtemp; i+=MODE_DIVISOR, j++);

switch (j)
	{
	case 0:
	proto_mode=FLYSKY_STD; 
	gpio_set(PORTD,LED_R);
	break;

	case 1:
	proto_mode=FLYSKY_MOD; 
	gpio_set(PORTD,LED_Y);
	break;

	case 2:
	proto_mode=HUBSAN_STD; 
	gpio_set(PORTD,LED_G);
	break;

	case 3:
	proto_mode=JP_NANOSTIK; 
	gpio_set(PORTD,LED_R);
	gpio_set(PORTD,LED_Y);
	while(1); //Not yet implimented so stop
	break;

	case 4:
	proto_mode=SPARE_PROTO1; 
	gpio_set(PORTD,LED_Y);
	gpio_set(PORTD,LED_G);
	while(1); //Not yet implimented so stop
	break;

	case 5:
	proto_mode=SPARE_PROTO2; 
	gpio_set(PORTD,LED_G);
	gpio_set(PORTD,LED_R);
	while(1); //Not yet implimented so stop
	break;

	case 6:
	proto_mode=SET_ID; 
	gpio_set(PORTD,LED_G);
	gpio_set(PORTD,LED_R);
	gpio_set(PORTD,LED_Y);
	break;
	}

if (proto_mode == SET_ID)
	{
	while (1)
		{
		if (!BIND_SW_READ()) break;
		_delay_ms(300);
		gpio_clear(PORTD,LED_G);
		gpio_clear(PORTD,LED_R);
		gpio_clear(PORTD,LED_Y);
		if (!BIND_SW_READ()) break;
		_delay_ms(300);
		gpio_set(PORTD,LED_G);
		gpio_set(PORTD,LED_R);
		gpio_set(PORTD,LED_Y);
		}
	gpio_set(PORTD,LED_G);
	gpio_set(PORTD,LED_R);
	gpio_set(PORTD,LED_Y);
	while (!BIND_SW_READ()); //Wait for button release
	eeprom_write_byte ((uint8_t*)5,0xFF); //Make sure a new tx id is picked at boot up
	eeprom_write_byte ((uint8_t*)6,0xFF); //Make sure a new tx id is picked at boot up
	while (!eeprom_is_ready()) {} //Make sure EEPROM write finishes
	//cli(); // disable interrupts
  	wdt_enable(WDTO_250MS); // enable watchdog
  	while(1); // wait for watchdog to reset processor 
	}


if (proto_mode == HUBSAN_STD) 
	{HUBSAN_Cmds(PROTOCMD_BIND); gpio_set(PORTD,LED_O);}

if (proto_mode == FLYSKY_MOD || proto_mode == FLYSKY_STD)
	{
	if (!BIND_SW_READ())
		{FLYSKY_Cmds(PROTOCMD_BIND);  gpio_set(PORTD,LED_O);}
	else
		{FLYSKY_Cmds(PROTOCMD_INIT);}
	}
	
if(!CH_ORD_READ()) g_spektrum_order = 1;
while (g_initializing) ; //wait until initialization has occured before re-enabling the PPM interrupt
gpio_clear(PORTD,LED_O);

// Enable Input Capture
g_need_to_sync = 1;
g_icr1_previous = ICR1;
TCCR1B |= (1<<ICNC1);

while (1) ;

}


// ******************************************************************************************
// ******                              Interrupt Routine                               ******
// ******************************************************************************************

ISR(TIMER1_CAPT_vect)
{
//each timer tick is half a microsecond
gpio_set(PORTB, DEBUG_1); //High
static uint16_t icr1_current; //static for debug
static int16_t icr1_diff;     //static for debug
int32_t tempch;

if (g_entropy==0) {g_entropy = TCNT1;}

icr1_current=ICR1; 
icr1_diff = icr1_current - g_icr1_previous;
g_icr1_previous = icr1_current;

if (g_servo_count < NUM_OUT_CHANNELS)
	{
	
	// > 3.0ms pulse seen as a frame sync
	if (icr1_diff > 6000)
   		{
   		g_servo_count=0;
   		g_need_to_sync = 0;
   		g_sync_count++;
   		}

	// Pulse within limits and we don't need to sync.	
	else if (!g_need_to_sync)
   		{
   		//1500us is servo centre pulse width
   		//2000L is CHAN_MAX_VALUE / 500us (max deviation from 1500us) * 100 (scaling)
   		//100L undoes the scaling
   		icr1_diff>>=1;
   		if (icr1_diff > 2000) icr1_diff=2000; // Range limiting
   		if (icr1_diff < 1000) icr1_diff=1000; // Range limiting
   		tempch = (int32_t)( ((icr1_diff - 1500L) * 2000L) /100L) ;
			
    	if(g_spektrum_order) // TAER order
			{
    		switch(g_servo_count)
				{
    			case 0:
    				Channels[2] = tempch;
    				break;
   				case 1:
    				Channels[0] = tempch;
    				break;
    			case 2:
    				Channels[1] = tempch;
    				break;
    			default:
					Channels[g_servo_count] = tempch;
				}
			}	
			
		else {Channels[g_servo_count] = tempch;}  //AETR order
				
   		g_servo_count++;
   		}
	}
else
	{
	g_servo_count=0;
   	g_need_to_sync = 0;
	}

gpio_clear(PORTB, DEBUG_1); //Low
}

