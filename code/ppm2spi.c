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
//#include "../../../../incs/uart.h"



#define BAUD 38400
#define NEUTRAL 0

// ******************************************************************************************
// ******                        Global Variables                                      ******
// ******************************************************************************************

volatile uint8_t g_servo_count = 0;
volatile uint8_t g_sync_count = 0;
volatile uint16_t g_icr1_previous = 0;
volatile uint8_t g_initializing = 1;
volatile uint8_t g_need_to_sync = 1;
struct Transmitter Transmitter;
struct Model Model;
volatile s16 Channels[NUM_OUT_CHANNELS];

int main (void)
{

char buffer[10];

//uart_init(UART_BAUD_SELECT((BAUD),F_CPU),TX_ONLY);

Model.fixed_id = 0x00102030;
Model.num_channels = 8;

gpio_set(DEBUG_DDR, DEBUG_ICR);
gpio_set(DEBUG_DDR, DEBUG_PACKET);
gpio_clear(DEBUG_DDR, PPM_IN); 

gpio_clear(SPI_DDR, BIND_SW);
gpio_set(SPI_PORT, BIND_SW);

// SPI INIT Bidirectional one wire mode, set to output
DATA_BI_OUT();
DATA_BI_LO();
DATA_PD_LOW();
CLK_OUT();
CLK_LO();
CS_OUT();
CS_HI();

// Set up for input capture on PD6
// Normal mode, OVF @ TOP (0xFFFF), F_CPU/8, noice cancler on ICP, falling edge trigger
TCCR1B = (1<<ICNC1) | (2<<CS10); // falling edge trigger 
//TCCR1B = (1<<ICNC1) | (2<<CS10) | (1<<ICES1); //rising edge trigger

// Enable ICP interrupt
TIMSK1 = (1<<ICIE1); 
// Global interrupt enable
sei();

while (g_sync_count <= 12) ;  //wait untill valid PPM signal

// Disable Input Capture
TCCR1B &= ~(1<<ICNC1);

if (BIND_SW_READ())
	FLYSKY_Cmds(PROTOCMD_INIT);
	//HUBSAN_Cmds(PROTOCMD_INIT);
else
	FLYSKY_Cmds(PROTOCMD_BIND);
	//HUBSAN_Cmds(PROTOCMD_BIND);

while (g_initializing) ; //wait until initialization has occured before re-enabling the PPM interrupt

// Enable Input Capture
g_need_to_sync = 1;
g_icr1_previous = ICR1;
TCCR1B |= (1<<ICNC1);

//uart_puts_p(PSTR("Hello World\r\n"));
while (1) ;

}


// ******************************************************************************************
// ******                              Interrupt Routine                               ******
// ******************************************************************************************

ISR(TIMER1_CAPT_vect)
{
//each timer tick is half a microsecond
gpio_set(DEBUG_PORT, DEBUG_ICR);
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

gpio_clear(DEBUG_PORT, DEBUG_ICR);
}

