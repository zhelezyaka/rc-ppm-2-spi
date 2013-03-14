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
 
void PROTOCOL_SetBindState(u32 msec);
void CLOCK_StopTimer();
u32 Crc(const void *buffer, u32 size);
void CLOCK_StartTimer(u16 us, u16 (*cb)(void));
