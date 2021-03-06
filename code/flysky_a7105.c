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

#ifdef MODULAR
  //Allows the linker to properly relocate
  #define FLYSKY_Cmds PROTO_Cmds
  #pragma long_calls
#endif

#include "common.h"
#include "iface_a7105.h"     // Edit by cam - Added
#include "misc.h"            // Edit by cam - Added
#include <avr/interrupt.h>   // Edit by cam - Added
//#include "interface.h"     // Edit by cam - Commented out
//#include "mixer.h"         // Edit by cam - Commented out
//#include "config/model.h"  // Edit by cam - Commented out
//#include "config/tx.h"     // Edit by cam - Commented out

#ifdef MODULAR
  #pragma long_calls_off
  extern unsigned _data_loadaddr;
  const unsigned long protocol_type = (unsigned long)&_data_loadaddr;
#endif

#ifdef PROTO_HAS_A7105

//Fewer bind packets in the emulator so we can get right to the important bits
#ifdef EMULATOR
#define BIND_COUNT 3
#else
#define BIND_COUNT 2500
#endif

static const u8 A7105_regs[] = {
     -1,  0x42, 0x00, 0x14, 0x00,  -1 ,  -1 , 0x00, 0x00, 0x00, 0x00, 0x01, 0x21, 0x05, 0x00, 0x50,
    0x9e, 0x4b, 0x00, 0x02, 0x16, 0x2b, 0x12, 0x00, 0x62, 0x80, 0x80, 0x00, 0x0a, 0x32, 0xc3, 0x0f,
    0x13, 0xc3, 0x00,  -1,  0x00, 0x00, 0x3b, 0x00, 0x17, 0x47, 0x80, 0x03, 0x01, 0x45, 0x18, 0x00,
    0x01, 0x0f,  -1,
};
static const u8 tx_channels[16][16] = {
  {0x0a, 0x5a, 0x14, 0x64, 0x1e, 0x6e, 0x28, 0x78, 0x32, 0x82, 0x3c, 0x8c, 0x46, 0x96, 0x50, 0xa0},
  {0xa0, 0x50, 0x96, 0x46, 0x8c, 0x3c, 0x82, 0x32, 0x78, 0x28, 0x6e, 0x1e, 0x64, 0x14, 0x5a, 0x0a},
  {0x0a, 0x5a, 0x50, 0xa0, 0x14, 0x64, 0x46, 0x96, 0x1e, 0x6e, 0x3c, 0x8c, 0x28, 0x78, 0x32, 0x82},
  {0x82, 0x32, 0x78, 0x28, 0x8c, 0x3c, 0x6e, 0x1e, 0x96, 0x46, 0x64, 0x14, 0xa0, 0x50, 0x5a, 0x0a},
  {0x28, 0x78, 0x0a, 0x5a, 0x50, 0xa0, 0x14, 0x64, 0x1e, 0x6e, 0x3c, 0x8c, 0x32, 0x82, 0x46, 0x96},
  {0x96, 0x46, 0x82, 0x32, 0x8c, 0x3c, 0x6e, 0x1e, 0x64, 0x14, 0xa0, 0x50, 0x5a, 0x0a, 0x78, 0x28},
  {0x50, 0xa0, 0x28, 0x78, 0x0a, 0x5a, 0x1e, 0x6e, 0x3c, 0x8c, 0x32, 0x82, 0x46, 0x96, 0x14, 0x64},
  {0x64, 0x14, 0x96, 0x46, 0x82, 0x32, 0x8c, 0x3c, 0x6e, 0x1e, 0x5a, 0x0a, 0x78, 0x28, 0xa0, 0x50},
  {0x50, 0xa0, 0x46, 0x96, 0x3c, 0x8c, 0x28, 0x78, 0x0a, 0x5a, 0x32, 0x82, 0x1e, 0x6e, 0x14, 0x64},
  {0x64, 0x14, 0x6e, 0x1e, 0x82, 0x32, 0x5a, 0x0a, 0x78, 0x28, 0x8c, 0x3c, 0x96, 0x46, 0xa0, 0x50},
  {0x46, 0x96, 0x3c, 0x8c, 0x50, 0xa0, 0x28, 0x78, 0x0a, 0x5a, 0x1e, 0x6e, 0x32, 0x82, 0x14, 0x64},
  {0x64, 0x14, 0x82, 0x32, 0x6e, 0x1e, 0x5a, 0x0a, 0x78, 0x28, 0xa0, 0x50, 0x8c, 0x3c, 0x96, 0x46},
  {0x46, 0x96, 0x0a, 0x5a, 0x3c, 0x8c, 0x14, 0x64, 0x50, 0xa0, 0x28, 0x78, 0x1e, 0x6e, 0x32, 0x82},
  {0x82, 0x32, 0x6e, 0x1e, 0x78, 0x28, 0xa0, 0x50, 0x64, 0x14, 0x8c, 0x3c, 0x5a, 0x0a, 0x96, 0x46},
  {0x46, 0x96, 0x0a, 0x5a, 0x50, 0xa0, 0x3c, 0x8c, 0x28, 0x78, 0x1e, 0x6e, 0x32, 0x82, 0x14, 0x64},
  {0x64, 0x14, 0x82, 0x32, 0x6e, 0x1e, 0x78, 0x28, 0x8c, 0x3c, 0xa0, 0x50, 0x5a, 0x0a, 0x96, 0x46},
};
static u32 id;
//static const u8 id[] = { 0x02, 0x00, 0x00, 0x70 };
static u8 chanrow;
static u8 chancol;
static u8 chanoffset;
static u8 packet[21];
static u16 counter;

static void flysky_init()
{
    int i;
    u8 if_calibration1;
    u8 vco_calibration0;
    u8 vco_calibration1;

    A7105_WriteID(0x5475c52a);
    for (i = 0; i < 0x33; i++)
        if((s8)A7105_regs[i] != -1)
            A7105_WriteReg(i, A7105_regs[i]);

    A7105_Strobe(A7105_STANDBY);

    //IF Filter Bank Calibration
    A7105_WriteReg(0x02, 1);
    A7105_ReadReg(0x02);
    while(A7105_ReadReg(0x02))
        ;
    if_calibration1 = A7105_ReadReg(0x22);
    if(if_calibration1 & A7105_MASK_FBCF) {
        //Calibration failed...what do we do?
    }

    //VCO Current Calibration
    A7105_WriteReg(0x24, 0x13); //Recomended calibration from A7105 Datasheet

    //VCO Bank Calibration
    A7105_WriteReg(0x26, 0x3b); //Recomended limits from A7105 Datasheet

    //VCO Bank Calibrate channel 0?
    //Set Channel
    A7105_WriteReg(0x0f, 0); //Should we choose a different channel?
    //VCO Calibration
    A7105_WriteReg(0x02, 2);
    while(A7105_ReadReg(0x02))
        ;
    vco_calibration0 = A7105_ReadReg(0x25);
    if (vco_calibration0 & A7105_MASK_VBCF) {
        //Calibration failed...what do we do?
    }

    //Calibrate channel 0xa0?
    //Set Channel
    A7105_WriteReg(0x0f, 0xa0); //Should we choose a different channel?
    //VCO Calibration
    A7105_WriteReg(0x02, 2);
    while(A7105_ReadReg(0x02))
        ;
    vco_calibration1 = A7105_ReadReg(0x25);
    if (vco_calibration1 & A7105_MASK_VBCF) {
        //Calibration failed...what do we do?
    }

    //Reset VCO Band calibration
    A7105_WriteReg(0x25, 0x08);

    A7105_Strobe(A7105_STANDBY);
}

static void flysky_build_packet(u8 init)
{
    int i;
    //-100% =~ 0x03e8
    //+100% =~ 0x07ca
    //Calculate:
    //Center = 0x5d9
    //1 %    = 5
    packet[0] = init ? 0xaa : 0x55;
    packet[1] = (id >>  0) & 0xff;
    packet[2] = (id >>  8) & 0xff;
    packet[3] = (id >> 16) & 0xff;
    packet[4] = (id >> 24) & 0xff;
    for (i = 0; i < 8; i++) {
        if (i > Model.num_channels) {
            packet[5 + i*2] = 0;
            packet[6 + i*2] = 0;
            continue;
        }
        s32 value = (s32)Channels[i] * 0x1f1 / CHAN_MAX_VALUE + 0x5d9;
        if (value < 0)
            value = 0;
        packet[5 + i*2] = value & 0xff;
        packet[6 + i*2] = (value >> 8) & 0xff;
    }

	if (proto_mode == FLYSKY_MOD) {
		// On threshold set as 400 = 1500us + 20us, so 20us above centre
        if(Channels[4] > 400)    
            packet[12] |= 0x20;  // Bit 13 of the rudder channel - JP Twister Quad LEDS
        if(Channels[5] > 400)
            packet[10] |= 0x40;  // Bit 14 of the throttle channel will toggle the accessory (video camera)
        if(Channels[6] > 400)
            packet[10] |= 0x80;  // Bit 15 of the throttle channel will toggle the accessory (still camera)
    }

	//if (Channels[4] > 3000) packet[12] |= 0x30;  //Edit by Cam - The quadcopter mod
}

//MODULE_CALLTYPE   //Edit by cam - Commented out
static u16 flysky_cb()
{

	gpio_set(PORTB, DEBUG_2); //High
    if (counter) {
        flysky_build_packet(1);
        A7105_WriteData(packet, 21, 1);
        counter--;
        if (! counter)
            PROTOCOL_SetBindState(0);
    } else {
		g_initializing = 0;   //Edit by cam - added to indicate normal data transmission has begun
        flysky_build_packet(0);
        A7105_WriteData(packet, 21, tx_channels[chanrow][chancol]-chanoffset);
        chancol = (chancol + 1) % 16;
        if (! chancol) //Keep transmit power updated  
           A7105_SetPower(Model.tx_power);  
    }

	gpio_clear(PORTB, DEBUG_2); //Low
    return 1460;
}

static void initialize(u8 bind) {
    CLOCK_StopTimer();
    A7105_Reset();
    flysky_init();
    if (Model.fixed_id) {
        id = Model.fixed_id;
    } else {
        id = (Crc(&Model, sizeof(Model)) + Crc(&Transmitter, sizeof(Transmitter))) % 999999;
    }
    chanrow = id % 16;
    chancol = 0;
    chanoffset = (id & 0xff) / 16;
    if (bind || ! Model.fixed_id) {
        counter = BIND_COUNT;
		//Edit by cam - (u16) to fix cast warning
        PROTOCOL_SetBindState((u16)2500 * 1460 / 1000); //msec
    } else {
        counter = 0;
    }
    CLOCK_StartTimer(2400, flysky_cb);
}

const void *FLYSKY_Cmds(enum ProtoCmds cmd)
//const void *FLYSKY_Cmds(enum ProtoCmds cmd)
{
    switch(cmd) {
        case PROTOCMD_INIT:  initialize(0); return 0;
        case PROTOCMD_DEINIT: return 0;
        case PROTOCMD_CHECK_AUTOBIND: return Model.fixed_id ? 0 : (void *)1L;
        case PROTOCMD_BIND:  initialize(1); return 0;
        case PROTOCMD_NUMCHAN: return (void *)8L;
        case PROTOCMD_DEFAULT_NUMCHAN: return (void *)8L;
		//Edit by cam - Here we cast id to a void pointer to a const memory location
		//On ARM void pointers are 32 bit, on AVR they are 16 bit, hence a compiler warning
		//We don't use this line so comment it out.
        //case PROTOCMD_CURRENT_ID: return (void *)((unsigned long)id);  
        case PROTOCMD_TELEMETRYSTATE: return (void *)(long)-1;
        default: break;
    }
    return 0;
}
#endif
