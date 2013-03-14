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

#ifndef PROTODEF

#else
#ifdef PROTO_HAS_CYRF6936
PROTODEF(PROTOCOL_DEVO,   EATRG, DEVO_Cmds, "DEVO")
PROTODEF(PROTOCOL_WK2801, EATRG, WK2x01_Cmds, "WK2801")
#ifndef DEFINE_FUNCS
PROTODEF(PROTOCOL_WK2601, EATRG, WK2x01_Cmds, "WK2601")
PROTODEF(PROTOCOL_WK2401, EATRG, WK2x01_Cmds, "WK2401")
PROTODEF(PROTOCOL_DSM2,   TAERG, DSM2_Cmds,   "DSM2")
#endif
PROTODEF(PROTOCOL_DSMX,   TAERG, DSM2_Cmds,   "DSMX")
PROTODEF(PROTOCOL_J6PRO,  AETRG, J6PRO_Cmds,  "J6Pro")
#endif //PROTO_HAS_CYRF6936
#ifdef PROTO_HAS_A7105
PROTODEF(PROTOCOL_FLYSKY, AETRG, FLYSKY_Cmds, "Flysky")
PROTODEF(PROTOCOL_HUBSAN, AETRG, HUBSAN_Cmds, "Hubsan4")
#endif //PROTO_HAS_A7105
PROTODEF(PROTOCOL_PPM,    EATRG, PPMOUT_Cmds, "PPM")
#endif //PROTODEF
