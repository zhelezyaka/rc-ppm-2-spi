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
#include <util/delay.h>

void spi_enable(u8 spi)
{}

void spi_disable(u8 spi)
{}

void spi_set_bidirectional_receive_only_mode(u8 spi)
{
// Bi directional one wire mode, set to input
DATA_BI_IN();
DATA_BI_LO(); //pull up off and set low
DATA_PD_FLOAT();
}

void spi_set_unidirectional_mode(u8 spi)
{
// Bi directional one wire mode, set to output
DATA_BI_LO(); //pull up off and set low
DATA_BI_OUT();
DATA_PD_LOW();
}

u8 spi_read(u8 spi)
{
   uint8_t i;
   uint8_t data=0;
   // send bits 7..0
   for (i = 0; i < 8; i++)
   {
       // shift byte left so next bit will be leftmost
       data <<= 1;

       CLK_HI();  //Data is read on the rising edge

       if (DATA_BI_READ())
           data |= 1;
       else
           data &= 0b11111110;
 
       // pulse clock to indicate that bit value should be read
      
       CLK_LO();  //Data transition is on the failing edge
 

   }
   return data;
}

// transmit byte serially, MSB first
u8 spi_xfer(u8 spi, u8 data)
{
   int i;
   // send bits 7..0
   for (i = 0; i < 8; i++)
   {
       // consider leftmost bit
       // set line high if bit is 1, low if bit is 0
       if (data & 0x80)
           DATA_BI_HI();
       else
           DATA_BI_LO();
	   // Setup time 		
	   asm volatile("nop"); 
	   asm volatile("nop"); 


       // pulse clock to indicate that bit value should be read
       CLK_HI();
	   asm volatile("nop"); 
       CLK_LO(); 
 
       // shift byte left so next bit will be leftmost
       data <<= 1;
   }
   return 0;
}
