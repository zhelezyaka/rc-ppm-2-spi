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
 
 This file is based on work by PhracturedBlue (real name and email ?)
 It can be found here:
 https://bitbucket.org/PhracturedBlue/deviation/src
 
 Alterations by Cameron Weeks <th9xer@gmail.com>
 http://code.google.com/p/rc-ppm-2-spi/
 */

#include "common.h"
#include <avr/interrupt.h>

//static u8 proto_state;
//static u32 bind_time;
u16 (*timer_callback)(void);
#define PROTO_READY   0x01
#define PROTO_BINDING 0x02
#define PROTO_BINDDLG 0x04

void PROTOCOL_SetBindState(u32 msec)
{
// Edit by Cam - Commented out
// This function appears to relay information back to the user about binding
// It's seems to just set a delay and display a "binding" message on the LCD
// For that duration. We don't have an LCD so it's commented out for now. May
// impliment in the future if needed with a LED for feedback. 
// Possible problem is the AVR has no ms counter, need to investigate.

/*    if (msec) {
        if (msec == 0xFFFFFFFF)
            bind_time = msec;
        else
            bind_time = CLOCK_getms() + msec;
        proto_state |= PROTO_BINDING;
    } else {
        proto_state &= ~PROTO_BINDING;
    } */
}

void CLOCK_StartTimer(u16 us, u16 (*cb)(void))
{
    if(! cb)
        return;
    timer_callback = cb;
    /* Set the capture compare value for OC1. */
    OCR1A = TCNT1 + (us<<1);
	// Enable Output-Compare interrrupts
	TIMSK1 |= (1<<OCIE1A); 

}

void CLOCK_StopTimer() {
	// Disable Output-Compare interrrupts
	TIMSK1 &= ~(1<<OCIE1A);
    timer_callback = NULL;
}

ISR(TIMER1_COMPA_vect)
{
    if(timer_callback) {
        u16 us = timer_callback();
        if (us) {
             OCR1A += (us<<1);
             return;
        }
    }
    CLOCK_StopTimer();
}

//The folloiwng code came from: http://notabs.org/winzipcrc/winzipcrc.c
// C99 winzip crc function, by Scott Duplichan
//We could use the internal CRC implementation in the STM32, but this is really small
//and perfomrance isn't really an issue
u32 Crc(const void *buffer, u32 size)
{
   u32 crc = ~0;
   const u8  *position = buffer;

   while (size--) 
      {
      int bit;
      crc ^= *position++;
      for (bit = 0; bit < 8; bit++) 
         {
         s32 out = crc & 1;
         crc >>= 1;
         crc ^= -out & 0xEDB88320;
         }
      }
   return ~crc;
}
