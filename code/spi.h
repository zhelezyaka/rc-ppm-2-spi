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

u8 spi_xfer(u8 spi, u8 data);
u8 spi_read(u8 spi);
void spi_enable(u8 spi);
void spi_disable(u8 spi);
void spi_set_bidirectional_receive_only_mode(u8 spi);
void spi_set_unidirectional_mode(u8 spi);
