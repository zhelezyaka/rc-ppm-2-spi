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
 */
 
#include "common.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define NEUTRAL 0
#define MARGIN 200 //10us

// ******************************************************************************************
// ******                        Global Variables                                      ******
// ******************************************************************************************

volatile uint8_t g_servo_count = 0;
volatile uint8_t g_sync_count = 0;
volatile uint16_t g_icr1_previous = 0;
volatile uint8_t g_initializing = 1;
volatile uint8_t g_need_to_sync = 1;
uint8_t proto_mode=FLYSKY;
struct Transmitter Transmitter;
struct Model Model;
volatile s16 Channels[NUM_OUT_CHANNELS];

s16 chtemp;
int main (void)
{

Model.fixed_id = 0x00102030;
Model.num_channels = 8;
Model.tx_power = TXPOWER_100mW ;

PORTB=0;
gpio_clear (DDRB, PPM_IN);  // Input  pin0
gpio_set   (DDRB, DEBUG_1); // Output pin1
gpio_set   (DDRB, DEBUG_2); // Output pin2 (SS output - General purpose output pin)
gpio_set   (DDRB,3);        // MOSI output 
gpio_clear (DDRB,4);        // MISO input
gpio_set   (DDRB,5);        // SCK output

PORTC=0;
gpio_clear (DDRC, BIND_SW);  // Input pin5
gpio_set   (PORTC,BIND_SW);  // Pull up resistor on pin5
gpio_set   (DDRC, SPI_CS);   // Output pin3

PORTD=0;
gpio_clear (DDRD, 0);  // Serial Rx input
gpio_set   (DDRD, 1);  // Serial Tx output
gpio_set   (DDRD, LED_G);  // LED green
gpio_set   (DDRD, LED_R);  // LED red
gpio_set   (DDRD, LED_Y);  // LED yellow
gpio_set   (DDRD, LED_O);  // LED yellow


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
//Clock polarity, idle low CPOL=0, Sample leading edge CPHA=0, 16/fosc SPR1=0 SPR0=1
SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);

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

chtemp = Channels[7];

if ( chtemp <= (CHAN_MIN_VALUE+MARGIN))                        
	{proto_mode=FLYSKY_STD; gpio_set(PORTD,LED_R);}
if ((chtemp <= (NEUTRAL+MARGIN     )) && (chtemp >= (NEUTRAL-MARGIN    ))) 
	{proto_mode=FLYSKY_MOD; gpio_set(PORTD,LED_Y);}
if ( chtemp >= (CHAN_MAX_VALUE-MARGIN))                        
	{proto_mode=HUBSAN_STD; gpio_set(PORTD,LED_G);}


if (proto_mode == HUBSAN_STD) 
	{HUBSAN_Cmds(PROTOCMD_BIND); gpio_set(PORTD,LED_O);}

if (proto_mode <= FLYSKY_MOD)
	{
	if (BIND_SW_READ())
		{FLYSKY_Cmds(PROTOCMD_BIND);  gpio_set(PORTD,LED_O);}
	else
		{FLYSKY_Cmds(PROTOCMD_INIT);}
	}

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

icr1_current=ICR1; 
icr1_diff = icr1_current - g_icr1_previous;
g_icr1_previous = icr1_current;

if (g_servo_count < NUM_OUT_CHANNELS)
	{
	if (icr1_diff > 6000) 
   		{
   		g_servo_count=0;
   		g_need_to_sync = 0;
   		g_sync_count++;
   		}
	else if (!g_need_to_sync)
   		{
   		//1500us is servo centre pulse width
   		//2000L is CHAN_MAX_VALUE / 500us (max deviation from 1500us) * 100 (scaling)
   		//100L undoes the scaling
   		icr1_diff>>=1;
   		if (icr1_diff > 2000) icr1_diff=2000;
   		if (icr1_diff < 1000) icr1_diff=1000;
   		Channels[g_servo_count] = (int32_t)( ((icr1_diff - 1500L) * 2000L) /100L) ;
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

