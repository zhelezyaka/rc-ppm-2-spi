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
 
#include <stdint.h>
#include <avr/io.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#include "iface_a7105.h"

enum TxPower {
    TXPOWER_100uW,
    TXPOWER_300uW,
    TXPOWER_1mW,
    TXPOWER_3mW,
    TXPOWER_10mW,
    TXPOWER_30mW,
    TXPOWER_100mW,
    TXPOWER_150mW,
    TXPOWER_LAST,
};

enum ProtoCmds {
    PROTOCMD_INIT,
    PROTOCMD_DEINIT,
    PROTOCMD_BIND,
    PROTOCMD_CHECK_AUTOBIND,
    PROTOCMD_NUMCHAN,
    PROTOCMD_DEFAULT_NUMCHAN,
    PROTOCMD_CURRENT_ID,
    PROTOCMD_SET_TXPOWER,
    PROTOCMD_GETOPTIONS,
    PROTOCMD_SETOPTIONS,
    PROTOCMD_TELEMETRYSTATE,
};

enum proto_mode {
    FLYSKY_STD,
    FLYSKY_MOD,
    HUBSAN_STD,
	JP_NANOSTIK,
	SPARE_PROTO1,
	SPARE_PROTO2,
	SET_ID
};

struct Model {
    u8 num_channels;
    u32 fixed_id;
    enum TxPower tx_power;
};
extern struct Model Model;

extern volatile uint8_t g_initializing;

extern uint8_t proto_mode;

struct Transmitter {
    u8 dummy;
};
extern struct Transmitter Transmitter;
extern const void *FLYSKY_Cmds(enum ProtoCmds cmd);
extern const void *HUBSAN_Cmds(enum ProtoCmds cmd);

#define NULL ((void *)0)

#define NUM_OUT_CHANNELS 16

//MAX = 10000
//MIN = -10000
#define CHAN_MULTIPLIER 100
#define CHAN_MAX_VALUE (100 * CHAN_MULTIPLIER)
#define CHAN_MIN_VALUE (-100 * CHAN_MULTIPLIER)
extern volatile s16 Channels[NUM_OUT_CHANNELS];

#define BIND_SW_READ() 	(PINC & (1<<BIND_SW))
#define CH_ORD_READ()   (PINC & (1<<CH_ORD))

#define SPI2 2

#define gpio_set(sfr,bit) (sfr) |=   1<<(bit)
#define gpio_clear(sfr,bit) (sfr) &= ~(1<<(bit))

//Port C
#define SPI_CS			3
#define CH_ORD          4
#define	BIND_SW			5

//Port B
#define PPM_IN			0
#define DEBUG_1		    1
#define DEBUG_2     	2

#define CS_HI() 		gpio_set(PORTC, SPI_CS)
#define CS_LO() 		gpio_clear(PORTC, SPI_CS) 

//Port D
#define LED_G 2  // LED green
#define LED_R 3  // LED red
#define LED_Y 4  // LED yellow
#define LED_O 5  // LED orange


/* Bit bang SPI, to delete
#define SPI_PORT	    PORTC
#define SPI_DDR         DDRC
#define SPI_PIN		    PINC

#define CS_OUT()    	gpio_set(SPI_DDR, SPI_CS)
#define SPI_DIO_PD		0
#define SPI_DIO			1
#define SPI_CLK			2
#define SPI_DO      	4

#define CLK_HI() 		gpio_set(SPI_PORT, SPI_CLK) 
#define CLK_LO() 		gpio_clear(SPI_PORT, SPI_CLK)
#define CLK_OUT()   	gpio_set(SPI_DDR,SPI_CLK)

#define DATA_BI_HI() 	gpio_set(SPI_PORT, SPI_DIO) 
#define DATA_BI_LO() 	gpio_clear(SPI_PORT, SPI_DIO)
#define DATA_BI_OUT()  	gpio_set(SPI_DDR, SPI_DIO)
#define DATA_BI_IN()	gpio_clear(SPI_DDR, SPI_DIO)
#define DATA_BI_READ() 	(SPI_PIN & (1<<SPI_DIO))

#define DATA_PD_FLOAT() gpio_clear(SPI_PORT, SPI_DIO_PD); gpio_clear(SPI_DDR, SPI_DIO_PD)
#define DATA_PD_LOW()	gpio_clear(SPI_PORT, SPI_DIO_PD); gpio_set(SPI_DDR, SPI_DIO_PD)

#define DATA_DO_HI()	gpio_set(SPI_PORT, SPI_DO)
#define DATA_DO_LO()	gpio_clear(SPI_PORT, SPI_DO)
#define DATA_DO_OUT()	gpio_set(SPI_DDR, SPI_DO)
*/



