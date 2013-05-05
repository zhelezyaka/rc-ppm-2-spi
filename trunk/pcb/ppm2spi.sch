EESchema Schematic File Version 2  date 05/05/2013 12:35:46
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ppm2spi
LIBS:ppm2spi-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ppm2spi Convertor"
Date "5 may 2013"
Rev "0.1"
Comp "Copyright Cameron Weeks <th9xer@gmail.com>"
Comment1 "Licensed under the TAPR Open Hardware License (www.tapr.org/OHL)"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_2 P5
U 1 1 5141D78A
P 6800 2600
F 0 "P5" V 6750 2600 40  0000 C CNN
F 1 "CONN_2" V 6850 2600 40  0000 C CNN
F 2 "" H 6800 2600 60  0001 C CNN
F 3 "" H 6800 2600 60  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 513E5CDC
P 5550 4200
F 0 "K1" V 5500 4200 50  0000 C CNN
F 1 "CONN_3" V 5600 4200 40  0000 C CNN
F 2 "" H 5550 4200 60  0001 C CNN
F 3 "" H 5550 4200 60  0001 C CNN
	1    5550 4200
	1    0    0    -1  
$EndComp
$Comp
L HOLE_M3 H4
U 1 1 513E0A97
P 1450 6800
F 0 "H4" H 1200 6700 60  0000 C CNN
F 1 "HOLE_M3" H 1350 6600 60  0000 C CNN
F 2 "" H 1450 6800 60  0001 C CNN
F 3 "" H 1450 6800 60  0001 C CNN
	1    1450 6800
	1    0    0    -1  
$EndComp
$Comp
L HOLE_M3 H3
U 1 1 513E0A91
P 1450 6550
F 0 "H3" H 1200 6450 60  0000 C CNN
F 1 "HOLE_M3" H 1350 6350 60  0000 C CNN
F 2 "" H 1450 6550 60  0001 C CNN
F 3 "" H 1450 6550 60  0001 C CNN
	1    1450 6550
	1    0    0    -1  
$EndComp
$Comp
L HOLE_M3 H2
U 1 1 513E0A8C
P 1450 6300
F 0 "H2" H 1200 6200 60  0000 C CNN
F 1 "HOLE_M3" H 1350 6100 60  0000 C CNN
F 2 "" H 1450 6300 60  0001 C CNN
F 3 "" H 1450 6300 60  0001 C CNN
	1    1450 6300
	1    0    0    -1  
$EndComp
$Comp
L HOLE_M3 H1
U 1 1 513E0A84
P 1450 6050
F 0 "H1" H 1200 5950 60  0000 C CNN
F 1 "HOLE_M3" H 1350 5850 60  0000 C CNN
F 2 "" H 1450 6050 60  0001 C CNN
F 3 "" H 1450 6050 60  0001 C CNN
	1    1450 6050
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 513E0904
P 5200 6850
F 0 "R11" V 5280 6850 50  0000 C CNN
F 1 "1K" V 5200 6850 50  0000 C CNN
F 2 "" H 5200 6850 60  0001 C CNN
F 3 "" H 5200 6850 60  0001 C CNN
	1    5200 6850
	0    -1   -1   0   
$EndComp
$Comp
L R R10
U 1 1 513E0902
P 5200 6500
F 0 "R10" V 5280 6500 50  0000 C CNN
F 1 "1K" V 5200 6500 50  0000 C CNN
F 2 "" H 5200 6500 60  0001 C CNN
F 3 "" H 5200 6500 60  0001 C CNN
	1    5200 6500
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 513E08E6
P 5200 6150
F 0 "R9" V 5280 6150 50  0000 C CNN
F 1 "1K" V 5200 6150 50  0000 C CNN
F 2 "" H 5200 6150 60  0001 C CNN
F 3 "" H 5200 6150 60  0001 C CNN
	1    5200 6150
	0    -1   -1   0   
$EndComp
Text Label 5000 4300 0    60   ~ 0
LED3
Text Label 5000 4200 0    60   ~ 0
LED2
Text Label 5000 4100 0    60   ~ 0
LED1
$Comp
L GND #PWR3
U 1 1 513E082D
P 2350 3400
F 0 "#PWR3" H 2350 3400 30  0001 C CNN
F 1 "GND" H 2350 3330 30  0001 C CNN
F 2 "" H 2350 3400 60  0001 C CNN
F 3 "" H 2350 3400 60  0001 C CNN
	1    2350 3400
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 513E0828
P 2350 3100
F 0 "C10" H 2400 3200 50  0000 L CNN
F 1 "100nF" H 2400 3000 50  0000 L CNN
F 2 "" H 2350 3100 60  0001 C CNN
F 3 "" H 2350 3100 60  0001 C CNN
	1    2350 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 513E07C2
P 2800 7150
F 0 "#PWR7" H 2800 7150 30  0001 C CNN
F 1 "GND" H 2800 7080 30  0001 C CNN
F 2 "" H 2800 7150 60  0001 C CNN
F 3 "" H 2800 7150 60  0001 C CNN
	1    2800 7150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR6
U 1 1 513E07BE
P 2800 5700
F 0 "#PWR6" H 2800 5790 20  0001 C CNN
F 1 "+5V" H 2800 5790 30  0000 C CNN
F 2 "" H 2800 5700 60  0001 C CNN
F 3 "" H 2800 5700 60  0001 C CNN
	1    2800 5700
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 513E07B8
P 2800 6000
F 0 "R8" V 2880 6000 50  0000 C CNN
F 1 "10K" V 2800 6000 50  0000 C CNN
F 2 "" H 2800 6000 60  0001 C CNN
F 3 "" H 2800 6000 60  0001 C CNN
	1    2800 6000
	-1   0    0    1   
$EndComp
$Comp
L C C9
U 1 1 513E07A8
P 2800 6900
F 0 "C9" H 2850 7000 50  0000 L CNN
F 1 "100nF" H 2850 6800 50  0000 L CNN
F 2 "" H 2800 6900 60  0001 C CNN
F 3 "" H 2800 6900 60  0001 C CNN
	1    2800 6900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR11
U 1 1 513E06E3
P 4250 6350
F 0 "#PWR11" H 4250 6440 20  0001 C CNN
F 1 "+5V" H 4250 6440 30  0000 C CNN
F 2 "" H 4250 6350 60  0001 C CNN
F 3 "" H 4250 6350 60  0001 C CNN
	1    4250 6350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 513E06E0
P 4150 6750
F 0 "#PWR10" H 4150 6750 30  0001 C CNN
F 1 "GND" H 4150 6680 30  0001 C CNN
F 2 "" H 4150 6750 60  0001 C CNN
F 3 "" H 4150 6750 60  0001 C CNN
	1    4150 6750
	1    0    0    -1  
$EndComp
Text Label 2950 6600 0    60   ~ 0
RESET
Text Label 2950 6500 0    60   ~ 0
SCK
Text Label 2950 6400 0    60   ~ 0
MISO
Text Label 4150 6500 0    60   ~ 0
MOSI
Text Label 5000 3750 0    60   ~ 0
RESET
Text Label 5000 2800 0    60   ~ 0
SCK
Text Label 5000 2700 0    60   ~ 0
MISO
Text Label 5000 2600 0    60   ~ 0
MOSI
$Comp
L CONN_3X2 P3
U 1 1 513E069B
P 3650 6550
F 0 "P3" H 3650 6800 50  0000 C CNN
F 1 "CONN_3X2" V 3650 6600 40  0000 C CNN
F 2 "" H 3650 6550 60  0001 C CNN
F 3 "" H 3650 6550 60  0001 C CNN
	1    3650 6550
	1    0    0    -1  
$EndComp
Text Label 5000 2500 0    60   ~ 0
DEBUG2
Text Label 5000 2400 0    60   ~ 0
DEBUG1
Text Label 4700 6850 0    60   ~ 0
LED3
Text Label 4700 6500 0    60   ~ 0
LED2
Text Label 4700 6150 0    60   ~ 0
LED1
$Comp
L GND #PWR12
U 1 1 513E05CD
P 6100 7100
F 0 "#PWR12" H 6100 7100 30  0001 C CNN
F 1 "GND" H 6100 7030 30  0001 C CNN
F 2 "" H 6100 7100 60  0001 C CNN
F 3 "" H 6100 7100 60  0001 C CNN
	1    6100 7100
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 513E05B3
P 6150 2300
F 0 "R7" V 6230 2300 50  0000 C CNN
F 1 "1K" V 6150 2300 50  0000 C CNN
F 2 "" H 6150 2300 60  0001 C CNN
F 3 "" H 6150 2300 60  0001 C CNN
	1    6150 2300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR5
U 1 1 513E05A6
P 2650 3900
F 0 "#PWR5" H 2650 3900 30  0001 C CNN
F 1 "GND" H 2650 3830 30  0001 C CNN
F 2 "" H 2650 3900 60  0001 C CNN
F 3 "" H 2650 3900 60  0001 C CNN
	1    2650 3900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR4
U 1 1 513E05A3
P 2650 3350
F 0 "#PWR4" H 2650 3440 20  0001 C CNN
F 1 "+5V" H 2650 3440 30  0000 C CNN
F 2 "" H 2650 3350 60  0001 C CNN
F 3 "" H 2650 3350 60  0001 C CNN
	1    2650 3350
	1    0    0    -1  
$EndComp
Text Label 6550 2300 0    60   ~ 0
PPM_IN
$Comp
L GND #PWR13
U 1 1 513E054D
P 6550 5100
F 0 "#PWR13" H 6550 5100 30  0001 C CNN
F 1 "GND" H 6550 5030 30  0001 C CNN
F 2 "" H 6550 5100 60  0001 C CNN
F 3 "" H 6550 5100 60  0001 C CNN
	1    6550 5100
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 513E0516
P 6150 4950
F 0 "SW1" H 6300 5060 50  0000 C CNN
F 1 "SW_PUSH" H 6150 4870 50  0000 C CNN
F 2 "" H 6150 4950 60  0001 C CNN
F 3 "" H 6150 4950 60  0001 C CNN
	1    6150 4950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR25
U 1 1 513E04F8
P 9950 5250
F 0 "#PWR25" H 9950 5210 30  0001 C CNN
F 1 "+3.3V" H 9950 5360 30  0000 C CNN
F 2 "" H 9950 5250 60  0001 C CNN
F 3 "" H 9950 5250 60  0001 C CNN
	1    9950 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 513E04F3
P 9950 5800
F 0 "#PWR26" H 9950 5800 30  0001 C CNN
F 1 "GND" H 9950 5730 30  0001 C CNN
F 2 "" H 9950 5800 60  0001 C CNN
F 3 "" H 9950 5800 60  0001 C CNN
	1    9950 5800
	1    0    0    -1  
$EndComp
$Comp
L CP C8
U 1 1 513E04ED
P 9950 5500
F 0 "C8" H 10000 5600 50  0000 L CNN
F 1 "10uf" H 10000 5400 50  0000 L CNN
F 2 "" H 9950 5500 60  0001 C CNN
F 3 "" H 9950 5500 60  0001 C CNN
	1    9950 5500
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR24
U 1 1 513E04BE
P 9950 3600
F 0 "#PWR24" H 9950 3560 30  0001 C CNN
F 1 "+3.3V" H 9950 3710 30  0000 C CNN
F 2 "" H 9950 3600 60  0001 C CNN
F 3 "" H 9950 3600 60  0001 C CNN
	1    9950 3600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR20
U 1 1 513E04B0
P 8550 4700
F 0 "#PWR20" H 8550 4700 30  0001 C CNN
F 1 "GND" H 8550 4630 30  0001 C CNN
F 2 "" H 8550 4700 60  0001 C CNN
F 3 "" H 8550 4700 60  0001 C CNN
	1    8550 4700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR9
U 1 1 513E045A
P 3000 2250
F 0 "#PWR9" H 3000 2340 20  0001 C CNN
F 1 "+5V" H 3000 2340 30  0000 C CNN
F 2 "" H 3000 2250 60  0001 C CNN
F 3 "" H 3000 2250 60  0001 C CNN
	1    3000 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 513E0448
P 2950 4750
F 0 "#PWR8" H 2950 4750 30  0001 C CNN
F 1 "GND" H 2950 4680 30  0001 C CNN
F 2 "" H 2950 4750 60  0001 C CNN
F 3 "" H 2950 4750 60  0001 C CNN
	1    2950 4750
	1    0    0    -1  
$EndComp
Text Label 6250 4050 0    60   ~ 0
CS
$Comp
L GND #PWR15
U 1 1 513E0385
P 7400 5800
F 0 "#PWR15" H 7400 5800 30  0001 C CNN
F 1 "GND" H 7400 5730 30  0001 C CNN
F 2 "" H 7400 5800 60  0001 C CNN
F 3 "" H 7400 5800 60  0001 C CNN
	1    7400 5800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR22
U 1 1 513E027A
P 9150 2350
F 0 "#PWR22" H 9150 2310 30  0001 C CNN
F 1 "+3.3V" H 9150 2460 30  0000 C CNN
F 2 "" H 9150 2350 60  0001 C CNN
F 3 "" H 9150 2350 60  0001 C CNN
	1    9150 2350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR21
U 1 1 513E0273
P 9150 1500
F 0 "#PWR21" H 9150 1590 20  0001 C CNN
F 1 "+5V" H 9150 1590 30  0000 C CNN
F 2 "" H 9150 1500 60  0001 C CNN
F 3 "" H 9150 1500 60  0001 C CNN
	1    9150 1500
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR2
U 1 1 513E01EB
P 1900 1350
F 0 "#PWR2" H 1900 1300 20  0001 C CNN
F 1 "+BATT" H 1900 1450 30  0000 C CNN
F 2 "" H 1900 1350 60  0001 C CNN
F 3 "" H 1900 1350 60  0001 C CNN
	1    1900 1350
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR18
U 1 1 513E01E7
P 8050 2400
F 0 "#PWR18" H 8050 2350 20  0001 C CNN
F 1 "+BATT" H 8050 2500 30  0000 C CNN
F 2 "" H 8050 2400 60  0001 C CNN
F 3 "" H 8050 2400 60  0001 C CNN
	1    8050 2400
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR16
U 1 1 513E01E0
P 8050 1550
F 0 "#PWR16" H 8050 1500 20  0001 C CNN
F 1 "+BATT" H 8050 1650 30  0000 C CNN
F 2 "" H 8050 1550 60  0001 C CNN
F 3 "" H 8050 1550 60  0001 C CNN
	1    8050 1550
	1    0    0    -1  
$EndComp
Text Label 1750 950  0    60   ~ 0
PPM_IN
$Comp
L GND #PWR1
U 1 1 513E01B7
P 1850 1700
F 0 "#PWR1" H 1850 1700 30  0001 C CNN
F 1 "GND" H 1850 1630 30  0001 C CNN
F 2 "" H 1850 1700 60  0001 C CNN
F 3 "" H 1850 1700 60  0001 C CNN
	1    1850 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 513E019B
P 8050 2050
F 0 "#PWR17" H 8050 2050 30  0001 C CNN
F 1 "GND" H 8050 1980 30  0001 C CNN
F 2 "" H 8050 2050 60  0001 C CNN
F 3 "" H 8050 2050 60  0001 C CNN
	1    8050 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 513E0198
P 8050 2900
F 0 "#PWR19" H 8050 2900 30  0001 C CNN
F 1 "GND" H 8050 2830 30  0001 C CNN
F 2 "" H 8050 2900 60  0001 C CNN
F 3 "" H 8050 2900 60  0001 C CNN
	1    8050 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 513E0151
P 6850 3800
F 0 "#PWR14" H 6850 3800 30  0001 C CNN
F 1 "GND" H 6850 3730 30  0001 C CNN
F 2 "" H 6850 3800 60  0001 C CNN
F 3 "" H 6850 3800 60  0001 C CNN
	1    6850 3800
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 513DD20F
P 5750 6850
F 0 "D3" H 5750 6950 50  0000 C CNN
F 1 "LED" H 5750 6750 50  0000 C CNN
F 2 "" H 5750 6850 60  0001 C CNN
F 3 "" H 5750 6850 60  0001 C CNN
	1    5750 6850
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 513DD20C
P 5750 6500
F 0 "D2" H 5750 6600 50  0000 C CNN
F 1 "LED" H 5750 6400 50  0000 C CNN
F 2 "" H 5750 6500 60  0001 C CNN
F 3 "" H 5750 6500 60  0001 C CNN
	1    5750 6500
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 513DD209
P 5750 6150
F 0 "D1" H 5750 6250 50  0000 C CNN
F 1 "LED" H 5750 6050 50  0000 C CNN
F 2 "" H 5750 6150 60  0001 C CNN
F 3 "" H 5750 6150 60  0001 C CNN
	1    5750 6150
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 513DD202
P 6850 3450
F 0 "C7" H 6900 3550 50  0000 L CNN
F 1 "18pF" H 6900 3350 50  0000 L CNN
F 2 "" H 6850 3450 60  0001 C CNN
F 3 "" H 6850 3450 60  0001 C CNN
	1    6850 3450
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 513DD1FF
P 6600 3450
F 0 "C6" H 6650 3550 50  0000 L CNN
F 1 "18pF" H 6650 3350 50  0000 L CNN
F 2 "" H 6600 3450 60  0001 C CNN
F 3 "" H 6600 3450 60  0001 C CNN
	1    6600 3450
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 513DD1F8
P 6700 3000
F 0 "X1" H 6700 3150 60  0000 C CNN
F 1 "16Mhz" H 6700 2850 60  0000 C CNN
F 2 "" H 6700 3000 60  0001 C CNN
F 3 "" H 6700 3000 60  0001 C CNN
	1    6700 3000
	-1   0    0    1   
$EndComp
$Comp
L CONN_5 P1
U 1 1 513DD1E4
P 1200 1400
F 0 "P1" V 1150 1400 50  0000 C CNN
F 1 "CONN_5" V 1250 1400 50  0000 C CNN
F 2 "" H 1200 1400 60  0001 C CNN
F 3 "" H 1200 1400 60  0001 C CNN
	1    1200 1400
	-1   0    0    -1  
$EndComp
$Comp
L CONN_6 P2
U 1 1 513DD1E1
P 9100 4200
F 0 "P2" V 9050 4200 60  0000 C CNN
F 1 "CONN_6" V 9150 4200 60  0000 C CNN
F 2 "" H 9100 4200 60  0001 C CNN
F 3 "" H 9100 4200 60  0001 C CNN
	1    9100 4200
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 513DD1C9
P 8050 2600
F 0 "C3" H 8100 2700 50  0000 L CNN
F 1 "10uf" H 8100 2500 50  0000 L CNN
F 2 "" H 8050 2600 60  0001 C CNN
F 3 "" H 8050 2600 60  0001 C CNN
	1    8050 2600
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 513DD1C6
P 8050 1750
F 0 "C2" H 8100 1850 50  0000 L CNN
F 1 "10uf" H 8100 1650 50  0000 L CNN
F 2 "" H 8050 1750 60  0001 C CNN
F 3 "" H 8050 1750 60  0001 C CNN
	1    8050 1750
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 513DD1BF
P 2650 3600
F 0 "C1" H 2700 3700 50  0000 L CNN
F 1 "100nF" H 2700 3500 50  0000 L CNN
F 2 "" H 2650 3600 60  0001 C CNN
F 3 "" H 2650 3600 60  0001 C CNN
	1    2650 3600
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 513DD1BD
P 9150 1750
F 0 "C5" H 9200 1850 50  0000 L CNN
F 1 "100nF" H 9200 1650 50  0000 L CNN
F 2 "" H 9150 1750 60  0001 C CNN
F 3 "" H 9150 1750 60  0001 C CNN
	1    9150 1750
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 513DD1B7
P 9150 2600
F 0 "C4" H 9200 2700 50  0000 L CNN
F 1 "100nf" H 9200 2500 50  0000 L CNN
F 2 "" H 9150 2600 60  0001 C CNN
F 3 "" H 9150 2600 60  0001 C CNN
	1    9150 2600
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 513DD1B3
P 7400 5450
F 0 "R6" V 7480 5450 50  0000 C CNN
F 1 "2K" V 7400 5450 50  0000 C CNN
F 2 "" H 7400 5450 60  0001 C CNN
F 3 "" H 7400 5450 60  0001 C CNN
	1    7400 5450
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 513DD1B2
P 7150 5450
F 0 "R5" V 7230 5450 50  0000 C CNN
F 1 "2K" V 7150 5450 50  0000 C CNN
F 2 "" H 7150 5450 60  0001 C CNN
F 3 "" H 7150 5450 60  0001 C CNN
	1    7150 5450
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 513DD1B0
P 7150 4600
F 0 "R4" V 7230 4600 50  0000 C CNN
F 1 "1K" V 7150 4600 50  0000 C CNN
F 2 "" H 7150 4600 60  0001 C CNN
F 3 "" H 7150 4600 60  0001 C CNN
	1    7150 4600
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 513DD1AD
P 7400 4600
F 0 "R3" V 7480 4600 50  0000 C CNN
F 1 "1K" V 7400 4600 50  0000 C CNN
F 2 "" H 7400 4600 60  0001 C CNN
F 3 "" H 7400 4600 60  0001 C CNN
	1    7400 4600
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 513DD1AA
P 6900 4600
F 0 "R2" V 6980 4600 50  0000 C CNN
F 1 "1K" V 6900 4600 50  0000 C CNN
F 2 "" H 6900 4600 60  0001 C CNN
F 3 "" H 6900 4600 60  0001 C CNN
	1    6900 4600
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 513DD1A7
P 6900 5450
F 0 "R1" V 6980 5450 50  0000 C CNN
F 1 "2K" V 6900 5450 50  0000 C CNN
F 2 "" H 6900 5450 60  0001 C CNN
F 3 "" H 6900 5450 60  0001 C CNN
	1    6900 5450
	1    0    0    -1  
$EndComp
$Comp
L 7805 U2
U 1 1 513DD1A2
P 8600 2450
F 0 "U2" H 8750 2254 60  0000 C CNN
F 1 "MCP1702-3.3v" H 8600 2650 60  0000 C CNN
F 2 "" H 8600 2450 60  0001 C CNN
F 3 "" H 8600 2450 60  0001 C CNN
	1    8600 2450
	1    0    0    -1  
$EndComp
$Comp
L 7805 U1
U 1 1 513DD19F
P 8600 1600
F 0 "U1" H 8750 1404 60  0000 C CNN
F 1 "MCP1702-5v" H 8600 1800 60  0000 C CNN
F 2 "" H 8600 1600 60  0001 C CNN
F 3 "" H 8600 1600 60  0001 C CNN
	1    8600 1600
	1    0    0    -1  
$EndComp
$Comp
L ATMEGA328-A IC1
U 1 1 513DD19A
P 3900 3400
F 0 "IC1" H 3200 4650 50  0000 L BNN
F 1 "ATMEGA328-A" H 4150 2000 50  0000 L BNN
F 2 "TQFP32" H 3350 2050 50  0001 C CNN
F 3 "" H 3900 3400 60  0001 C CNN
	1    3900 3400
	1    0    0    -1  
$EndComp
Text Label 6250 4250 0    60   ~ 0
MOSI
Text Label 6250 4350 0    60   ~ 0
MISO
Text Label 6250 4150 0    60   ~ 0
SCK
$Comp
L CONN_9 P4
U 1 1 518641B8
P 10400 4200
F 0 "P4" V 10350 4200 60  0000 C CNN
F 1 "CONN_9" V 10450 4200 60  0000 C CNN
F 2 "" H 10400 4200 60  0000 C CNN
F 3 "" H 10400 4200 60  0000 C CNN
	1    10400 4200
	1    0    0    -1  
$EndComp
Text Label 8300 3950 0    60   ~ 0
CS_3v
Text Label 8300 4050 0    60   ~ 0
SCK_3v
Text Label 8300 4150 0    60   ~ 0
DIO_3v
Text Label 9600 3900 0    60   ~ 0
CS_3v
$Comp
L GND #PWR23
U 1 1 518641D2
P 9550 4750
F 0 "#PWR23" H 9550 4750 30  0001 C CNN
F 1 "GND" H 9550 4680 30  0001 C CNN
F 2 "" H 9550 4750 60  0001 C CNN
F 3 "" H 9550 4750 60  0001 C CNN
	1    9550 4750
	1    0    0    -1  
$EndComp
Text Label 9600 4100 0    60   ~ 0
SCK_3v
Text Label 9600 4200 0    60   ~ 0
DIO_3v
Text Notes 9800 3150 0    60   ~ 0
AliExpress 500m\nModule
Text Notes 8500 3150 0    60   ~ 0
JP Twister Quad\nModule
Text Notes 9200 4000 0    60   ~ 0
SCS
Text Notes 9200 4100 0    60   ~ 0
SCK
Text Notes 9200 4200 0    60   ~ 0
SDIO
Text Notes 9200 4300 0    60   ~ 0
GPIO
Text Notes 9200 4400 0    60   ~ 0
GND
Text Notes 9200 4500 0    60   ~ 0
3.3V
Text Notes 10500 3850 0    60   ~ 0
Vcc
Text Notes 10500 3950 0    60   ~ 0
SCS
Text Notes 10500 4050 0    60   ~ 0
GND
Text Notes 10500 4150 0    60   ~ 0
SCK
Text Notes 10500 4250 0    60   ~ 0
SDIO
Text Notes 10500 4350 0    60   ~ 0
GIO1
Text Notes 10500 4450 0    60   ~ 0
GIO2
Text Notes 10500 4550 0    60   ~ 0
RXEN
Text Notes 10500 4650 0    60   ~ 0
TXEN
Text Notes 8450 3400 0    60   ~ 0
Silkscreen labels from modules are in blue
Text Notes 4800 5200 0    60   ~ 0
Bind switch.\nOnly does anything with Flysky protocol.\nHubsan protocol aways binds.
Text Notes 6200 6500 0    60   ~ 0
LEDs.\nCurrently do nothing.
Text Notes 5450 1750 0    60   ~ 0
Debug pins.\nCurrently show interrupt timing.\nFor use with oscilloscope.
$Comp
L JUMPER JP1
U 1 1 518648DA
P 5650 3350
F 0 "JP1" H 5650 3500 60  0000 C CNN
F 1 "JUMPER" H 5650 3270 40  0000 C CNN
F 2 "~" H 5650 3350 60  0000 C CNN
F 3 "~" H 5650 3350 60  0000 C CNN
	1    5650 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 2700 6150 2700
Wire Wire Line
	6150 2700 6150 2500
Wire Wire Line
	6150 2500 4900 2500
Wire Wire Line
	4900 3900 5650 3900
Wire Wire Line
	5200 4200 4900 4200
Wire Wire Line
	8750 4150 8050 4150
Wire Wire Line
	8750 3950 7750 3950
Wire Wire Line
	4950 6500 4700 6500
Wire Wire Line
	5550 6850 5450 6850
Wire Wire Line
	5550 6150 5450 6150
Wire Wire Line
	2350 3400 2350 3300
Connection ~ 3000 2400
Wire Wire Line
	3000 2250 3000 2600
Wire Wire Line
	2800 5750 2800 5700
Wire Wire Line
	2800 6600 3250 6600
Wire Wire Line
	2950 6500 3250 6500
Wire Wire Line
	4150 6750 4150 6600
Wire Wire Line
	4150 6600 4050 6600
Wire Wire Line
	4250 6350 4250 6400
Wire Wire Line
	4250 6400 4050 6400
Wire Wire Line
	4900 2700 5200 2700
Wire Wire Line
	4900 3750 5250 3750
Wire Wire Line
	4900 2900 6250 2900
Connection ~ 6100 6850
Wire Wire Line
	6100 6850 5950 6850
Wire Wire Line
	6400 2300 6900 2300
Wire Wire Line
	2650 3800 2650 3900
Wire Wire Line
	5850 4950 5800 4950
Wire Wire Line
	9950 5250 9950 5300
Wire Wire Line
	8550 4700 8550 4350
Wire Wire Line
	7900 5000 7900 4050
Connection ~ 7150 5000
Wire Wire Line
	7900 5000 7150 5000
Connection ~ 3000 2300
Connection ~ 2950 4500
Wire Wire Line
	3000 4500 2950 4500
Wire Wire Line
	7150 4350 7150 4150
Wire Wire Line
	7400 4850 7400 5200
Wire Wire Line
	6900 4850 6900 5200
Wire Wire Line
	6900 5700 7400 5700
Wire Wire Line
	9150 1500 9150 1550
Wire Wire Line
	9150 1550 9000 1550
Connection ~ 8600 2800
Wire Wire Line
	8050 2800 9150 2800
Wire Wire Line
	1850 1700 1850 1500
Wire Wire Line
	1850 1500 1600 1500
Wire Wire Line
	1900 1350 1900 1400
Wire Wire Line
	1900 1400 1600 1400
Wire Wire Line
	8050 2800 8050 2900
Wire Wire Line
	8050 1550 8200 1550
Wire Wire Line
	8050 2050 8050 1950
Wire Wire Line
	6600 3650 6850 3650
Connection ~ 7000 3000
Wire Wire Line
	7000 2800 7000 3250
Wire Wire Line
	7000 3250 6850 3250
Wire Wire Line
	6250 2900 6250 2800
Wire Wire Line
	6250 2800 7000 2800
Wire Wire Line
	6600 3250 6400 3250
Wire Wire Line
	6400 3250 6400 3000
Wire Wire Line
	6850 3650 6850 3800
Wire Wire Line
	8600 1950 8600 1850
Wire Wire Line
	8200 2400 8050 2400
Wire Wire Line
	8600 2700 8600 2800
Wire Wire Line
	1600 1200 1600 950 
Wire Wire Line
	1600 950  2050 950 
Wire Wire Line
	9000 2400 9150 2400
Wire Wire Line
	8050 1950 9150 1950
Connection ~ 8600 1950
Wire Wire Line
	9150 2400 9150 2350
Wire Wire Line
	7400 5700 7400 5800
Wire Wire Line
	7150 4850 7150 5200
Wire Wire Line
	7400 4050 7400 4350
Wire Wire Line
	6900 4350 6900 4250
Wire Wire Line
	3000 4400 2950 4400
Wire Wire Line
	2950 4400 2950 4750
Wire Wire Line
	3000 4600 2950 4600
Connection ~ 2950 4600
Wire Wire Line
	7400 4900 7750 4900
Connection ~ 7400 4900
Wire Wire Line
	7750 4900 7750 3950
Wire Wire Line
	8050 4150 8050 5100
Wire Wire Line
	8050 5100 6750 5100
Connection ~ 6900 5100
Wire Wire Line
	8750 4450 8750 4800
Wire Wire Line
	8750 4800 8900 4800
Wire Wire Line
	9950 5700 9950 5800
Wire Wire Line
	6550 5100 6550 4950
Wire Wire Line
	6550 4950 6450 4950
Wire Wire Line
	2650 3400 2650 3350
Wire Wire Line
	5950 6150 6100 6150
Wire Wire Line
	6100 6150 6100 7100
Wire Wire Line
	6100 6500 5950 6500
Connection ~ 6100 6500
Wire Wire Line
	6400 3000 4900 3000
Wire Wire Line
	4900 2300 5900 2300
Wire Wire Line
	4900 2600 5200 2600
Wire Wire Line
	4900 2800 5200 2800
Wire Wire Line
	4050 6500 4350 6500
Wire Wire Line
	3250 6400 2950 6400
Wire Wire Line
	2800 6250 2800 6700
Connection ~ 2800 6600
Wire Wire Line
	2800 7100 2800 7150
Wire Wire Line
	3000 2900 2350 2900
Wire Wire Line
	4900 4100 5200 4100
Wire Wire Line
	5550 6500 5450 6500
Wire Wire Line
	4950 6150 4700 6150
Wire Wire Line
	4950 6850 4700 6850
Wire Wire Line
	8550 4350 8750 4350
Wire Wire Line
	5200 4300 4900 4300
Wire Wire Line
	4900 2400 6300 2400
Wire Wire Line
	6300 2400 6300 2500
Wire Wire Line
	6300 2500 6450 2500
Connection ~ 7150 5700
Wire Wire Line
	7400 4050 6250 4050
Wire Wire Line
	7150 4150 6250 4150
Wire Wire Line
	6900 4250 6250 4250
Wire Wire Line
	6750 5100 6750 4350
Wire Wire Line
	6750 4350 6250 4350
Wire Wire Line
	7900 4050 8750 4050
Wire Wire Line
	9550 4000 10050 4000
Wire Wire Line
	9550 4000 9550 4750
Wire Wire Line
	10050 3800 9950 3800
Wire Wire Line
	9950 3600 9950 4600
Wire Wire Line
	9950 4600 10050 4600
Connection ~ 9950 3800
Wire Wire Line
	10050 3900 9600 3900
Wire Wire Line
	10050 4100 9600 4100
Wire Wire Line
	10050 4200 9600 4200
Wire Wire Line
	4900 3650 5550 3650
Wire Wire Line
	5550 3650 5550 4000
Wire Wire Line
	5550 4000 5800 4000
Wire Wire Line
	5800 4000 5800 4950
Wire Wire Line
	5650 3900 5650 3650
Wire Wire Line
	5650 3050 5650 2300
Connection ~ 5650 2300
Text Notes 5750 3550 0    60   ~ 0
LEAVE OPEN
Text Notes 3200 1050 0    60   ~ 0
JP1. Currently unused.\nMight be used in the future for more\nadvanced comminication with the module.
$EndSCHEMATC
