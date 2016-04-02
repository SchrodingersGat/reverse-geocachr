EESchema Schematic File Version 2
LIBS:USB_Geocache-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:memory
LIBS:interface
LIBS:nxp_armmcu
LIBS:dc-dc
LIBS:switches
LIBS:sensors
LIBS:display
LIBS:ftdi
LIBS:diode
LIBS:74xgxx
LIBS:74xx
LIBS:ac-dc
LIBS:analog_devices
LIBS:atmel
LIBS:maxim
LIBS:microchip
LIBS:microchip_dspic33dsc
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:msp430
LIBS:onsemi
LIBS:opto
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:relays
LIBS:rfcom
LIBS:silabs
LIBS:Currawong
LIBS:USB_Geocache-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "USB Reverse Geocache"
Date "2016-04-02"
Rev "Rev C"
Comp "Oliver Walters"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 1400 2050 0    60   ~ 0
D+
Text Label 1400 1950 0    60   ~ 0
D-
$Comp
L CONN_01X06 P3
U 1 1 546E9DF6
P 10050 4100
F 0 "P3" H 10050 4450 60  0000 C CNN
F 1 "SWD" V 10175 4100 60  0000 C CNN
F 2 "Components:POGO_Connector" H 10050 4100 60  0001 C CNN
F 3 "" H 10050 4100 60  0000 C CNN
	1    10050 4100
	-1   0    0    -1  
$EndComp
Text Label 2300 3500 0    60   ~ 0
LCD_CS
Text Label 2300 4000 0    60   ~ 0
LCD_RESET
Text Label 2300 3400 0    60   ~ 0
LCD_DC
Text Label 2300 3600 0    60   ~ 0
SPI_MOSI
Text Label 2300 3800 0    60   ~ 0
SPI_SCK
Text Label 2300 3700 0    60   ~ 0
SPI_MISO
$Comp
L C C11
U 1 1 546EAFE6
P 8950 4300
F 0 "C11" H 8950 4400 40  0000 L CNN
F 1 "18pF" H 8956 4215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8988 4150 30  0001 C CNN
F 3 "" H 8950 4300 60  0000 C CNN
	1    8950 4300
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 546EB082
P 7950 4300
F 0 "C6" H 7950 4400 40  0000 L CNN
F 1 "18pF" H 7956 4215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7988 4150 30  0001 C CNN
F 3 "Kemet:C0805C180J5GACTU." H 7950 4300 60  0001 C CNN
F 4 "E14:1609375 " H 7950 4300 60  0001 C CNN "Vendor"
	1    7950 4300
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR01
U 1 1 546EC41F
P 5075 975
F 0 "#PWR01" H 5075 925 20  0001 C CNN
F 1 "+BATT" H 5075 1075 30  0000 C CNN
F 2 "" H 5075 975 60  0000 C CNN
F 3 "" H 5075 975 60  0000 C CNN
	1    5075 975 
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 546EC4CB
P 5075 1325
F 0 "C8" H 5075 1425 40  0000 L CNN
F 1 "0.1uF" H 5081 1240 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5113 1175 30  0001 C CNN
F 3 "" H 5075 1325 60  0000 C CNN
	1    5075 1325
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR_SMALL L1
U 1 1 546EC764
P 6575 1050
F 0 "L1" H 6575 1150 50  0000 C CNN
F 1 "10uH" H 6575 1000 50  0000 C CNN
F 2 "Resistors_SMD:R_1210_HandSoldering" H 6575 1050 60  0001 C CNN
F 3 "TY:LBC3225T100KR" H 6575 1050 60  0001 C CNN
F 4 "E14:1836609" H 6575 1050 60  0001 C CNN "Vendor"
	1    6575 1050
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 546EC908
P 7200 1325
F 0 "C13" H 7200 1425 40  0000 L CNN
F 1 "10uF" H 7206 1240 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7238 1175 30  0001 C CNN
F 3 "" H 7200 1325 60  0000 C CNN
	1    7200 1325
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 546ECBF1
P 7200 1000
F 0 "#PWR02" H 7200 960 30  0001 C CNN
F 1 "+3.3V" H 7200 1110 30  0000 C CNN
F 2 "" H 7200 1000 60  0000 C CNN
F 3 "" H 7200 1000 60  0000 C CNN
	1    7200 1000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P7
U 1 1 546ED880
P 3275 6625
F 0 "P7" H 3275 6825 50  0000 C CNN
F 1 "Servo" V 3375 6625 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x03" H 3275 6625 60  0001 C CNN
F 3 "" H 3275 6625 60  0000 C CNN
	1    3275 6625
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 546EE047
P 2800 1350
F 0 "C3" H 2800 1450 40  0000 L CNN
F 1 "4.7uF" H 2806 1265 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2838 1200 30  0001 C CNN
F 3 "" H 2800 1350 60  0000 C CNN
	1    2800 1350
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR03
U 1 1 546EE72C
P 4650 950
F 0 "#PWR03" H 4650 900 20  0001 C CNN
F 1 "+BATT" H 4650 1050 30  0000 C CNN
F 2 "" H 4650 950 60  0000 C CNN
F 3 "" H 4650 950 60  0000 C CNN
	1    4650 950 
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 546EE92C
P 4475 1475
F 0 "R7" V 4555 1475 40  0000 C CNN
F 1 "2K" V 4482 1476 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4405 1475 30  0001 C CNN
F 3 "" H 4475 1475 30  0000 C CNN
	1    4475 1475
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 546EED93
P 4650 1350
F 0 "C4" H 4650 1450 40  0000 L CNN
F 1 "4.7uF" H 4656 1265 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4688 1200 30  0001 C CNN
F 3 "" H 4650 1350 60  0000 C CNN
	1    4650 1350
	1    0    0    -1  
$EndComp
Text Notes 3100 875  0    60   ~ 0
Battery Charging
Text Notes 5325 800  0    60   ~ 0
3.3v Supply (LDO)
$Comp
L +3.3V #PWR04
U 1 1 546F0A72
P 1600 4850
F 0 "#PWR04" H 1600 4810 30  0001 C CNN
F 1 "+3.3V" H 1600 4960 30  0000 C CNN
F 2 "" H 1600 4850 60  0000 C CNN
F 3 "" H 1600 4850 60  0000 C CNN
	1    1600 4850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 546F0D9C
P 1725 5225
F 0 "C1" H 1725 5325 40  0000 L CNN
F 1 "0.1uF" H 1731 5140 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1763 5075 30  0001 C CNN
F 3 "" H 1725 5225 60  0000 C CNN
	1    1725 5225
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 546F5A2B
P 2575 5375
F 0 "R3" V 2655 5375 40  0000 C CNN
F 1 "4K7" V 2582 5376 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2505 5375 30  0001 C CNN
F 3 "" H 2575 5375 30  0000 C CNN
	1    2575 5375
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR05
U 1 1 546F5E48
P 2575 5050
F 0 "#PWR05" H 2575 5010 30  0001 C CNN
F 1 "+3.3V" H 2575 5160 30  0000 C CNN
F 2 "" H 2575 5050 60  0000 C CNN
F 3 "" H 2575 5050 60  0000 C CNN
	1    2575 5050
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 546F65E3
P 2025 5225
F 0 "C2" H 2025 5325 40  0000 L CNN
F 1 "10uF" H 2031 5140 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2063 5075 30  0001 C CNN
F 3 "" H 2025 5225 60  0000 C CNN
	1    2025 5225
	1    0    0    -1  
$EndComp
Text Label 1800 7300 2    60   ~ 0
SERVO_EN
Text Label 3100 6300 0    60   ~ 0
SERVO_SIGNAL
$Comp
L C C16
U 1 1 54EA7958
P 7450 1325
F 0 "C16" H 7450 1425 40  0000 L CNN
F 1 "0.1uF" H 7456 1240 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7488 1175 30  0001 C CNN
F 3 "" H 7450 1325 60  0000 C CNN
	1    7450 1325
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL_SMD X1
U 1 1 5592365B
P 8425 4000
F 0 "X1" H 8425 4090 50  0000 C CNN
F 1 "12.000MHz" H 8175 4175 50  0000 L CNN
F 2 "Components:crystal_SMD_5032" H 8425 4000 60  0001 C CNN
F 3 "" H 8425 4000 60  0000 C CNN
	1    8425 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 55923A65
P 8425 4200
F 0 "#PWR06" H 8425 3950 50  0001 C CNN
F 1 "GND" H 8425 4050 50  0000 C CNN
F 2 "" H 8425 4200 60  0000 C CNN
F 3 "" H 8425 4200 60  0000 C CNN
	1    8425 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5592594A
P 5450 6150
F 0 "#PWR07" H 5450 5900 50  0001 C CNN
F 1 "GND" H 5450 6000 50  0000 C CNN
F 2 "" H 5450 6150 60  0000 C CNN
F 3 "" H 5450 6150 60  0000 C CNN
	1    5450 6150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR08
U 1 1 55925D75
P 5450 2500
F 0 "#PWR08" H 5450 2350 50  0001 C CNN
F 1 "+3.3V" H 5450 2640 50  0000 C CNN
F 2 "" H 5450 2500 60  0000 C CNN
F 3 "" H 5450 2500 60  0000 C CNN
	1    5450 2500
	1    0    0    -1  
$EndComp
Text Label 6750 5600 0    60   ~ 0
XIN
Text Label 6750 5700 0    60   ~ 0
XOUT
Text Label 9000 3950 0    60   ~ 0
XIN
Text Label 7875 3950 2    60   ~ 0
XOUT
$Comp
L C C5
U 1 1 5592A8B2
P 5700 2800
F 0 "C5" H 5725 2900 50  0000 L CNN
F 1 "10uF" H 5725 2700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5738 2650 30  0001 C CNN
F 3 "" H 5700 2800 60  0000 C CNN
	1    5700 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5592A92F
P 5700 3000
F 0 "#PWR09" H 5700 2750 50  0001 C CNN
F 1 "GND" H 5700 2850 50  0000 C CNN
F 2 "" H 5700 3000 60  0000 C CNN
F 3 "" H 5700 3000 60  0000 C CNN
	1    5700 3000
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5592AC39
P 5900 2800
F 0 "C7" H 5925 2900 50  0000 L CNN
F 1 "0.1uF" H 5925 2700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5938 2650 30  0001 C CNN
F 3 "" H 5900 2800 60  0000 C CNN
	1    5900 2800
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5592ACEE
P 6125 2800
F 0 "C9" H 6150 2900 50  0000 L CNN
F 1 "0.1uF" H 6150 2700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 6163 2650 30  0001 C CNN
F 3 "" H 6125 2800 60  0000 C CNN
	1    6125 2800
	1    0    0    -1  
$EndComp
Text Label 6825 5200 0    60   ~ 0
D+
Text Label 6825 5300 0    60   ~ 0
D-
Text Label 6900 4500 0    60   ~ 0
GPS_RX
Text Label 3725 4200 0    60   ~ 0
SPI_MISO
Text Label 3725 4300 0    60   ~ 0
SPI_MOSI
Text Label 3300 4400 0    60   ~ 0
SW_CLK
Text Label 3850 4900 0    60   ~ 0
SW_DIO
Text Label 6950 4800 0    60   ~ 0
SPI_SCK
Text Label 3750 3400 0    60   ~ 0
SW_RESET
$Comp
L +3.3V #PWR010
U 1 1 55925DCC
P 10450 3700
F 0 "#PWR010" H 10450 3550 50  0001 C CNN
F 1 "+3.3V" H 10450 3840 50  0000 C CNN
F 2 "" H 10450 3700 60  0000 C CNN
F 3 "" H 10450 3700 60  0000 C CNN
	1    10450 3700
	1    0    0    -1  
$EndComp
Text Label 10500 3950 0    60   ~ 0
SW_DIO
Text Label 10500 4050 0    60   ~ 0
SW_CLK
Text Label 10500 4250 0    60   ~ 0
SW_RESET
$Comp
L GND #PWR011
U 1 1 55926425
P 10800 4400
F 0 "#PWR011" H 10800 4150 50  0001 C CNN
F 1 "GND" H 10800 4250 50  0000 C CNN
F 2 "" H 10800 4400 60  0000 C CNN
F 3 "" H 10800 4400 60  0000 C CNN
	1    10800 4400
	1    0    0    -1  
$EndComp
Text Label 2775 5675 0    60   ~ 0
GPS_RX
Text Label 9000 5500 0    60   ~ 0
SPI_MOSI
Text Label 9000 5600 0    60   ~ 0
SPI_MISO
Text Label 9000 5400 0    60   ~ 0
SPI_SCK
Text Label 7600 5600 0    60   ~ 0
EEPROM_CS
Text Label 6725 3400 0    60   ~ 0
LCD_RESET
Text Label 6725 3500 0    60   ~ 0
LCD_CS
Text Label 4150 4800 2    60   ~ 0
LCD_DC
Text Label 6750 4300 0    60   ~ 0
SERVO_SIGNAL
$Comp
L +5V #PWR012
U 1 1 5594B98E
P 1250 1800
F 0 "#PWR012" H 1250 1650 50  0001 C CNN
F 1 "+5V" H 1250 1940 50  0000 C CNN
F 2 "" H 1250 1800 60  0000 C CNN
F 3 "" H 1250 1800 60  0000 C CNN
	1    1250 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5594C089
P 1300 2250
F 0 "#PWR013" H 1300 2000 50  0001 C CNN
F 1 "GND" H 1300 2100 50  0000 C CNN
F 2 "" H 1300 2250 60  0000 C CNN
F 3 "" H 1300 2250 60  0000 C CNN
	1    1300 2250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 5594D3E7
P 1750 1200
F 0 "P2" H 1750 1350 50  0000 C CNN
F 1 "Battery" V 1850 1200 50  0000 C CNN
F 2 "Connectors_JST:JST_PH_S02B-PH-K-S_02x2.00mm_Angled" H 1750 1200 60  0001 C CNN
F 3 "" H 1750 1200 60  0000 C CNN
	1    1750 1200
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5594D7E9
P 2050 1300
F 0 "#PWR014" H 2050 1050 50  0001 C CNN
F 1 "GND" H 2050 1150 50  0000 C CNN
F 2 "" H 2050 1300 60  0000 C CNN
F 3 "" H 2050 1300 60  0000 C CNN
	1    2050 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR015
U 1 1 5594DB80
P 2800 950
F 0 "#PWR015" H 2800 800 50  0001 C CNN
F 1 "+5V" H 2800 1090 50  0000 C CNN
F 2 "" H 2800 950 60  0000 C CNN
F 3 "" H 2800 950 60  0000 C CNN
	1    2800 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5594E618
P 2800 1550
F 0 "#PWR016" H 2800 1300 50  0001 C CNN
F 1 "GND" H 2800 1400 50  0000 C CNN
F 2 "" H 2800 1550 60  0000 C CNN
F 3 "" H 2800 1550 60  0000 C CNN
	1    2800 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5594F8EC
P 4650 1625
F 0 "#PWR017" H 4650 1375 50  0001 C CNN
F 1 "GND" H 4650 1475 50  0000 C CNN
F 2 "" H 4650 1625 60  0000 C CNN
F 3 "" H 4650 1625 60  0000 C CNN
	1    4650 1625
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5594F97F
P 5075 1650
F 0 "#PWR018" H 5075 1400 50  0001 C CNN
F 1 "GND" H 5075 1500 50  0000 C CNN
F 2 "" H 5075 1650 60  0000 C CNN
F 3 "" H 5075 1650 60  0000 C CNN
	1    5075 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5594FB35
P 4475 1875
F 0 "#PWR019" H 4475 1625 50  0001 C CNN
F 1 "GND" H 4475 1725 50  0000 C CNN
F 2 "" H 4475 1875 60  0000 C CNN
F 3 "" H 4475 1875 60  0000 C CNN
	1    4475 1875
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 5594FF27
P 7450 1525
F 0 "#PWR020" H 7450 1275 50  0001 C CNN
F 1 "GND" H 7450 1375 50  0000 C CNN
F 2 "" H 7450 1525 60  0000 C CNN
F 3 "" H 7450 1525 60  0000 C CNN
	1    7450 1525
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 5595018C
P 7200 1525
F 0 "#PWR021" H 7200 1275 50  0001 C CNN
F 1 "GND" H 7200 1375 50  0000 C CNN
F 2 "" H 7200 1525 60  0000 C CNN
F 3 "" H 7200 1525 60  0000 C CNN
	1    7200 1525
	1    0    0    -1  
$EndComp
$Comp
L USB_Mini_B P1
U 1 1 55952BD2
P 900 2050
F 0 "P1" V 600 2150 50  0000 C CNN
F 1 "USB_Mini_B" H 850 2250 50  0000 C CNN
F 2 "Connect:USB_Mini-B" V 850 1950 60  0001 C CNN
F 3 "" V 850 1950 60  0000 C CNN
	1    900  2050
	0    -1   1    0   
$EndComp
$Comp
L +BATT #PWR022
U 1 1 5595E68C
P 1500 6525
F 0 "#PWR022" H 1500 6375 50  0001 C CNN
F 1 "+BATT" H 1500 6665 50  0000 C CNN
F 2 "" H 1500 6525 60  0000 C CNN
F 3 "" H 1500 6525 60  0000 C CNN
	1    1500 6525
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5595E922
P 1700 7000
F 0 "R1" V 1780 7000 50  0000 C CNN
F 1 "4K7" V 1700 7000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1630 7000 30  0001 C CNN
F 3 "" H 1700 7000 30  0000 C CNN
	1    1700 7000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR023
U 1 1 5594EB35
P 1750 4350
F 0 "#PWR023" H 1750 4100 50  0001 C CNN
F 1 "GND" H 1750 4200 50  0000 C CNN
F 2 "" H 1750 4350 60  0000 C CNN
F 3 "" H 1750 4350 60  0000 C CNN
	1    1750 4350
	1    0    0    -1  
$EndComp
Text Label 4100 4100 2    60   ~ 0
EEPROM_CS
$Comp
L +BATT #PWR024
U 1 1 5596D4B8
P 2050 1100
F 0 "#PWR024" H 2050 950 50  0001 C CNN
F 1 "+BATT" H 2050 1240 50  0000 C CNN
F 2 "" H 2050 1100 60  0000 C CNN
F 3 "" H 2050 1100 60  0000 C CNN
	1    2050 1100
	1    0    0    -1  
$EndComp
Text Label 4050 5000 2    60   ~ 0
BATT_STAT
$Comp
L CONN_01X04 P4
U 1 1 559B297F
P 1225 5625
F 0 "P4" H 1225 5875 50  0000 C CNN
F 1 "GPS" V 1325 5625 50  0000 C CNN
F 2 "Connectors_JST:JST_PH_S04B-PH-K-S_04x2.00mm_Angled" H 1225 5625 60  0001 C CNN
F 3 "" H 1225 5625 60  0000 C CNN
	1    1225 5625
	-1   0    0    -1  
$EndComp
Text Label 1550 5775 0    60   ~ 0
GPS_TX
$Comp
L +5V #PWR025
U 1 1 55A39EC9
P 3825 3700
F 0 "#PWR025" H 3825 3550 50  0001 C CNN
F 1 "+5V" H 3825 3840 50  0000 C CNN
F 2 "" H 3825 3700 60  0000 C CNN
F 3 "" H 3825 3700 60  0000 C CNN
	1    3825 3700
	0    -1   -1   0   
$EndComp
Text Label 5375 1250 0    60   ~ 0
EN
Text Label 6800 3900 0    60   ~ 0
SERVO_EN
$Comp
L LM3670MF-RESCUE-USB_Geocache U4
U 1 1 55B58591
P 5825 1150
F 0 "U4" H 5625 1425 50  0000 L CNN
F 1 "LM3670MF" H 5625 1350 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 5825 950 50  0001 C CNN
F 3 "" H 5825 850 50  0000 C CIN
	1    5825 1150
	1    0    0    -1  
$EndComp
$Comp
L MCP73831/OT-RESCUE-USB_Geocache U1
U 1 1 55B6F8B3
P 3825 1175
F 0 "U1" H 3625 1425 50  0000 L CNN
F 1 "MCP73831/OT" H 3625 925 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 3625 825 50  0001 L CNN
F 3 "" H 3675 1125 60  0000 C CNN
	1    3825 1175
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR026
U 1 1 55C00D40
P 1750 3000
F 0 "#PWR026" H 1750 2850 50  0001 C CNN
F 1 "+3.3V" H 1750 3140 50  0000 C CNN
F 2 "" H 1750 3000 60  0000 C CNN
F 3 "" H 1750 3000 60  0000 C CNN
	1    1750 3000
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 55C010A3
P 1450 3050
F 0 "C12" H 1475 3150 50  0000 L CNN
F 1 "10uF" H 1475 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 1488 2900 30  0001 C CNN
F 3 "" H 1450 3050 60  0000 C CNN
	1    1450 3050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR027
U 1 1 55C0146F
P 1200 3050
F 0 "#PWR027" H 1200 2800 50  0001 C CNN
F 1 "GND" H 1200 2900 50  0000 C CNN
F 2 "" H 1200 3050 60  0000 C CNN
F 3 "" H 1200 3050 60  0000 C CNN
	1    1200 3050
	0    1    1    0   
$EndComp
Text Label 6800 4100 0    60   ~ 0
Enable
$Comp
L +3.3V #PWR028
U 1 1 55C050FA
P 8550 5100
F 0 "#PWR028" H 8550 4950 50  0001 C CNN
F 1 "+3.3V" H 8550 5240 50  0000 C CNN
F 2 "" H 8550 5100 60  0000 C CNN
F 3 "" H 8550 5100 60  0000 C CNN
	1    8550 5100
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 55C053BA
P 8900 5050
F 0 "C10" H 8925 5150 50  0000 L CNN
F 1 "0.1uF" H 8925 4950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8938 4900 30  0001 C CNN
F 3 "" H 8900 5050 60  0000 C CNN
	1    8900 5050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR029
U 1 1 55C05804
P 9150 5050
F 0 "#PWR029" H 9150 4800 50  0001 C CNN
F 1 "GND" H 9150 4900 50  0000 C CNN
F 2 "" H 9150 5050 60  0000 C CNN
F 3 "" H 9150 5050 60  0000 C CNN
	1    9150 5050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR030
U 1 1 55C07041
P 8550 5850
F 0 "#PWR030" H 8550 5600 50  0001 C CNN
F 1 "GND" H 8550 5700 50  0000 C CNN
F 2 "" H 8550 5850 60  0000 C CNN
F 3 "" H 8550 5850 60  0000 C CNN
	1    8550 5850
	1    0    0    -1  
$EndComp
$Comp
L 25LC_EEPROM U5
U 1 1 55C7F2D5
P 8550 5500
F 0 "U5" H 8250 5250 50  0000 L CNN
F 1 "25LC640A-I/SN" H 8600 5250 50  0000 L CNN
F 2 "SOIC_Packages:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 8200 5450 50  0001 C CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en532046" H 8200 5450 50  0001 C CNN
	1    8550 5500
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small JP1
U 1 1 55C803FA
P 3475 3625
F 0 "JP1" H 3475 3705 50  0000 C CNN
F 1 "Jumper_NO_Small" H 3485 3565 50  0001 C CNN
F 2 "Capacitors_SMD:C_0805" H 3475 3625 60  0001 C CNN
F 3 "" H 3475 3625 60  0000 C CNN
	1    3475 3625
	0    1    1    0   
$EndComp
$Comp
L LPC11U24FBD48 U3
U 1 1 55D95919
P 5450 4700
F 0 "U3" H 4400 6150 50  0000 C CNN
F 1 "LPC11U24FBD48" H 4650 3480 50  0000 C CNN
F 2 "QFP:LQFP-48_7x7mm_Pitch0.5mm" H 6400 3500 50  0001 C CNN
F 3 "" H 5450 3225 50  0001 C CNN
	1    5450 4700
	1    0    0    -1  
$EndComp
$Comp
L ILI9341_LCD_Breakout U2
U 1 1 55D9696E
P 1350 3700
F 0 "U2" H 650 4200 50  0000 L CNN
F 1 "ILI9341_LCD_Breakout" H 650 3200 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x09" H 600 4100 50  0001 C CNN
F 3 "" H 700 4200 50  0000 C CNN
	1    1350 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 56AB5EAB
P 8950 4500
F 0 "#PWR031" H 8950 4250 50  0001 C CNN
F 1 "GND" H 8950 4350 50  0000 C CNN
F 2 "" H 8950 4500 50  0000 C CNN
F 3 "" H 8950 4500 50  0000 C CNN
	1    8950 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 56AB6377
P 7950 4500
F 0 "#PWR032" H 7950 4250 50  0001 C CNN
F 1 "GND" H 7950 4350 50  0000 C CNN
F 2 "" H 7950 4500 50  0000 C CNN
F 3 "" H 7950 4500 50  0000 C CNN
	1    7950 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 56AB7DCE
P 2200 7600
F 0 "#PWR033" H 2200 7350 50  0001 C CNN
F 1 "GND" H 2200 7450 50  0000 C CNN
F 2 "" H 2200 7600 50  0000 C CNN
F 3 "" H 2200 7600 50  0000 C CNN
	1    2200 7600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 56AB8421
P 2950 7200
F 0 "#PWR034" H 2950 6950 50  0001 C CNN
F 1 "GND" H 2950 7050 50  0000 C CNN
F 2 "" H 2950 7200 50  0000 C CNN
F 3 "" H 2950 7200 50  0000 C CNN
	1    2950 7200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 56AB93D6
P 1650 5575
F 0 "#PWR035" H 1650 5325 50  0001 C CNN
F 1 "GND" H 1650 5425 50  0000 C CNN
F 2 "" H 1650 5575 50  0000 C CNN
F 3 "" H 1650 5575 50  0000 C CNN
	1    1650 5575
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 56B9C012
P 8750 1650
F 0 "P5" H 8750 1800 50  0000 C CNN
F 1 "Button" V 8850 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8750 1650 50  0001 C CNN
F 3 "" H 8750 1650 50  0000 C CNN
	1    8750 1650
	-1   0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 56B9C08F
P 9050 1900
F 0 "R10" V 9130 1900 50  0000 C CNN
F 1 "4K7" V 9050 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8980 1900 50  0001 C CNN
F 3 "" H 9050 1900 50  0000 C CNN
	1    9050 1900
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 56B9C147
P 9050 1400
F 0 "R6" V 9130 1400 50  0000 C CNN
F 1 "4K7" V 9050 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 8980 1400 50  0001 C CNN
F 3 "" H 9050 1400 50  0000 C CNN
	1    9050 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 56B9C3FF
P 9050 2150
F 0 "#PWR036" H 9050 1900 50  0001 C CNN
F 1 "GND" H 9050 2000 50  0000 C CNN
F 2 "" H 9050 2150 50  0000 C CNN
F 3 "" H 9050 2150 50  0000 C CNN
	1    9050 2150
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR037
U 1 1 56B9C58D
P 9050 1150
F 0 "#PWR037" H 9050 1000 50  0001 C CNN
F 1 "+BATT" H 9050 1290 50  0000 C CNN
F 2 "" H 9050 1150 50  0000 C CNN
F 3 "" H 9050 1150 50  0000 C CNN
	1    9050 1150
	1    0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 56B9C9E0
P 9350 1700
F 0 "D2" H 9350 1800 50  0000 C CNN
F 1 "D" H 9350 1600 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 9350 1700 50  0001 C CNN
F 3 "" H 9350 1700 50  0000 C CNN
	1    9350 1700
	-1   0    0    1   
$EndComp
Text Label 9300 1500 0    60   ~ 0
Button
$Comp
L D D3
U 1 1 56B9CD72
P 9600 1950
F 0 "D3" H 9600 2050 50  0000 C CNN
F 1 "D" H 9600 1850 50  0000 C CNN
F 2 "Diodes_SMD:SOD-123" H 9600 1950 50  0001 C CNN
F 3 "" H 9600 1950 50  0000 C CNN
	1    9600 1950
	0    1    1    0   
$EndComp
$Comp
L R R11
U 1 1 56B9CF47
P 9800 1900
F 0 "R11" V 9880 1900 50  0000 C CNN
F 1 "4K7" V 9800 1900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9730 1900 50  0001 C CNN
F 3 "" H 9800 1900 50  0000 C CNN
	1    9800 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 56B9D0A7
P 9800 2150
F 0 "#PWR038" H 9800 1900 50  0001 C CNN
F 1 "GND" H 9800 2000 50  0000 C CNN
F 2 "" H 9800 2150 50  0000 C CNN
F 3 "" H 9800 2150 50  0000 C CNN
	1    9800 2150
	1    0    0    -1  
$EndComp
Text Label 9800 1600 0    60   ~ 0
EN
Text Label 9550 2250 2    60   ~ 0
Enable
Text Label 3825 4500 0    60   ~ 0
Button
$Comp
L GND #PWR039
U 1 1 56BA0ED1
P 3475 3775
F 0 "#PWR039" H 3475 3525 50  0001 C CNN
F 1 "GND" H 3475 3625 50  0000 C CNN
F 2 "" H 3475 3775 50  0000 C CNN
F 3 "" H 3475 3775 50  0000 C CNN
	1    3475 3775
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 56BA1050
P 3475 3250
F 0 "R2" V 3555 3250 50  0000 C CNN
F 1 "4K7" V 3475 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3405 3250 50  0001 C CNN
F 3 "" H 3475 3250 50  0000 C CNN
	1    3475 3250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR040
U 1 1 56BA1325
P 3475 3000
F 0 "#PWR040" H 3475 2850 50  0001 C CNN
F 1 "+3.3V" H 3475 3140 50  0000 C CNN
F 2 "" H 3475 3000 50  0000 C CNN
F 3 "" H 3475 3000 50  0000 C CNN
	1    3475 3000
	1    0    0    -1  
$EndComp
Text Notes 1650 850  0    60   ~ 0
Battery Connector
$Comp
L +3.3V #PWR041
U 1 1 56BB1E05
P 2800 3000
F 0 "#PWR041" H 2800 2850 50  0001 C CNN
F 1 "+3.3V" H 2800 3140 50  0000 C CNN
F 2 "" H 2800 3000 50  0000 C CNN
F 3 "" H 2800 3000 50  0000 C CNN
	1    2800 3000
	1    0    0    -1  
$EndComp
Text Label 6900 4600 0    60   ~ 0
GPS_TX
Text Label 3475 1675 0    60   ~ 0
BATT_STAT
$Comp
L R R4
U 1 1 546EE2D1
P 3225 1275
F 0 "R4" V 3305 1275 40  0000 C CNN
F 1 "470" V 3232 1276 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3155 1275 30  0001 C CNN
F 3 "" H 3225 1275 30  0000 C CNN
	1    3225 1275
	0    1    1    0   
$EndComp
$Comp
L Q_NMOS_GSD Q2
U 1 1 56FADC79
P 2100 7300
F 0 "Q2" H 2400 7350 50  0000 R CNN
F 1 "DMP3098L" H 2750 7250 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 2300 7400 50  0001 C CNN
F 3 "" H 2100 7300 50  0000 C CNN
	1    2100 7300
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 56FAE083
P 1850 7500
F 0 "R5" V 1930 7500 50  0000 C CNN
F 1 "4K7" V 1850 7500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1780 7500 50  0001 C CNN
F 3 "" H 1850 7500 50  0000 C CNN
	1    1850 7500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR042
U 1 1 56FAE211
P 1850 7700
F 0 "#PWR042" H 1850 7450 50  0001 C CNN
F 1 "GND" H 1850 7550 50  0000 C CNN
F 2 "" H 1850 7700 50  0000 C CNN
F 3 "" H 1850 7700 50  0000 C CNN
	1    1850 7700
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 56FAE718
P 2850 6050
F 0 "R8" V 2930 6050 40  0000 C CNN
F 1 "4K7" V 2857 6051 40  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2780 6050 30  0001 C CNN
F 3 "" H 2850 6050 30  0000 C CNN
	1    2850 6050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR043
U 1 1 56FAE8DA
P 2850 5850
F 0 "#PWR043" H 2850 5810 30  0001 C CNN
F 1 "+3.3V" H 2850 5960 30  0000 C CNN
F 2 "" H 2850 5850 60  0000 C CNN
F 3 "" H 2850 5850 60  0000 C CNN
	1    2850 5850
	1    0    0    -1  
$EndComp
$Comp
L Q_PMOS_GSD Q1
U 1 1 56FB039A
P 2025 6725
F 0 "Q1" H 2325 6775 50  0000 R CNN
F 1 "SSM3J328R" H 2675 6675 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 2225 6825 50  0001 C CNN
F 3 "" H 2025 6725 50  0000 C CNN
	1    2025 6725
	0    1    -1   0   
$EndComp
$Comp
L Q_PMOS_GSD Q3
U 1 1 56FF5893
P 2900 3550
F 0 "Q3" H 2900 3800 50  0000 R CNN
F 1 "SSM3J328R" H 2900 3725 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" H 3100 3650 50  0001 C CNN
F 3 "" H 2900 3550 50  0000 C CNN
	1    2900 3550
	-1   0    0    1   
$EndComp
$Comp
L R R9
U 1 1 56FF60C4
P 3100 3250
F 0 "R9" V 3180 3250 50  0000 C CNN
F 1 "4K7" V 3100 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3030 3250 50  0001 C CNN
F 3 "" H 3100 3250 50  0000 C CNN
	1    3100 3250
	1    0    0    -1  
$EndComp
Text Label 3175 3550 0    60   ~ 0
BL
Text Label 6950 4900 0    60   ~ 0
BL
$Comp
L R R12
U 1 1 56FF88CD
P 2950 6950
F 0 "R12" V 3030 6950 50  0000 C CNN
F 1 "0R1" V 2950 6950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2880 6950 50  0001 C CNN
F 3 "" H 2950 6950 50  0000 C CNN
F 4 "1% 0.25W" H 3275 6950 50  0000 C CNN "Rating"
	1    2950 6950
	1    0    0    -1  
$EndComp
Text Label 2825 6725 2    60   ~ 0
Rsense
Wire Wire Line
	8950 3950 8950 4150
Wire Wire Line
	5075 975  5075 1175
Wire Wire Line
	5075 1050 5525 1050
Connection ~ 5075 1050
Wire Wire Line
	5075 1475 5075 1650
Wire Wire Line
	5300 1150 5525 1150
Wire Wire Line
	5300 1150 5300 1575
Wire Wire Line
	5300 1575 5075 1575
Connection ~ 5075 1575
Wire Wire Line
	6825 1050 7450 1050
Wire Wire Line
	7075 1250 7075 1050
Wire Wire Line
	6125 1250 7075 1250
Wire Wire Line
	7200 1000 7200 1175
Connection ~ 7075 1050
Connection ~ 7200 1050
Wire Wire Line
	2800 950  2800 1200
Connection ~ 2800 1075
Wire Wire Line
	4650 950  4650 1200
Wire Wire Line
	4125 1075 4650 1075
Wire Wire Line
	4475 1175 4475 1325
Wire Wire Line
	4475 1625 4475 1875
Wire Wire Line
	4325 1275 4325 1800
Wire Wire Line
	4325 1800 4475 1800
Connection ~ 4475 1800
Connection ~ 4650 1075
Wire Wire Line
	4650 1500 4650 1625
Wire Wire Line
	1425 5575 1650 5575
Wire Wire Line
	1425 5675 2775 5675
Wire Wire Line
	1575 5575 1575 5475
Wire Wire Line
	1575 5475 2025 5475
Wire Wire Line
	1725 5375 1725 5475
Connection ~ 1575 5575
Wire Wire Line
	1600 5425 1525 5425
Wire Wire Line
	1600 4850 1600 5425
Wire Wire Line
	1725 4950 1725 5075
Wire Wire Line
	2575 5525 2575 5675
Connection ~ 2575 5675
Wire Wire Line
	2575 5050 2575 5225
Wire Wire Line
	1525 5425 1525 5475
Wire Wire Line
	1600 4950 2025 4950
Wire Wire Line
	2025 4950 2025 5075
Connection ~ 1600 4950
Wire Wire Line
	2025 5475 2025 5375
Connection ~ 1725 5475
Wire Wire Line
	2950 6800 2950 6725
Wire Wire Line
	2825 6725 3075 6725
Wire Wire Line
	2225 6625 3075 6625
Wire Wire Line
	1500 6625 1825 6625
Wire Wire Line
	2850 6200 2850 6525
Wire Wire Line
	2850 6525 3075 6525
Wire Wire Line
	7450 1050 7450 1175
Wire Wire Line
	8425 4100 8425 4200
Wire Wire Line
	7950 4000 8225 4000
Wire Wire Line
	8625 4000 8950 4000
Wire Wire Line
	9000 3950 8950 3950
Connection ~ 8950 4000
Wire Wire Line
	7875 3950 7950 3950
Connection ~ 7950 4000
Wire Wire Line
	5700 2950 5700 3000
Wire Wire Line
	5450 2575 6125 2575
Wire Wire Line
	5700 2575 5700 2650
Connection ~ 5450 2575
Wire Wire Line
	6125 2575 6125 2650
Connection ~ 5700 2575
Wire Wire Line
	5900 2575 5900 2650
Connection ~ 5900 2575
Wire Wire Line
	5700 2975 6125 2975
Wire Wire Line
	6125 2975 6125 2950
Connection ~ 5700 2975
Wire Wire Line
	5900 2950 5900 2975
Connection ~ 5900 2975
Wire Wire Line
	10450 3700 10450 3850
Wire Wire Line
	10450 3850 10250 3850
Wire Wire Line
	10500 3950 10250 3950
Wire Wire Line
	10500 4050 10250 4050
Wire Wire Line
	10500 4250 10250 4250
Wire Wire Line
	10800 4400 10800 4350
Wire Wire Line
	10800 4350 10250 4350
Wire Wire Line
	5550 6100 5550 6000
Wire Wire Line
	5350 6100 5550 6100
Connection ~ 5450 6100
Wire Wire Line
	6750 5700 6650 5700
Wire Wire Line
	6750 5600 6650 5600
Wire Wire Line
	3725 4200 4250 4200
Wire Wire Line
	3725 4300 4250 4300
Wire Wire Line
	3300 4400 4250 4400
Wire Wire Line
	3750 3400 4250 3400
Wire Wire Line
	3850 4900 4250 4900
Wire Wire Line
	3825 4500 4250 4500
Wire Wire Line
	1250 1800 1250 1850
Wire Wire Line
	1250 1850 1200 1850
Wire Wire Line
	1400 1950 1200 1950
Wire Wire Line
	1400 2050 1200 2050
Wire Wire Line
	1200 2150 1300 2150
Wire Wire Line
	1300 2150 1300 2250
Wire Wire Line
	1950 1150 2050 1150
Wire Wire Line
	2050 1300 2050 1250
Wire Wire Line
	2050 1250 1950 1250
Wire Wire Line
	2800 1550 2800 1500
Wire Wire Line
	2800 1075 3525 1075
Wire Wire Line
	7200 1475 7200 1525
Wire Wire Line
	7450 1475 7450 1525
Wire Wire Line
	6825 5300 6650 5300
Wire Wire Line
	6825 5200 6650 5200
Wire Wire Line
	5350 2875 5550 2875
Connection ~ 5450 2875
Wire Wire Line
	3100 6300 2850 6300
Wire Wire Line
	1500 6525 1500 7000
Wire Wire Line
	1500 7000 1550 7000
Connection ~ 1500 6625
Wire Wire Line
	1850 7000 2200 7000
Wire Wire Line
	2025 7000 2025 6925
Connection ~ 2025 7000
Wire Wire Line
	2050 1150 2050 1100
Wire Wire Line
	3825 3700 4250 3700
Connection ~ 1725 4950
Wire Wire Line
	1525 5475 1425 5475
Wire Wire Line
	6325 1050 6125 1050
Wire Wire Line
	1550 5775 1425 5775
Wire Wire Line
	3475 3500 4250 3500
Connection ~ 3000 1075
Wire Wire Line
	3375 1275 3525 1275
Wire Wire Line
	3475 1675 3400 1675
Wire Wire Line
	3400 1675 3400 1275
Connection ~ 3400 1275
Wire Wire Line
	5375 1250 5525 1250
Wire Wire Line
	6725 3400 6650 3400
Wire Wire Line
	6725 3500 6650 3500
Wire Wire Line
	5450 6100 5450 6150
Wire Wire Line
	5350 6000 5350 6100
Wire Wire Line
	5550 2875 5550 3200
Wire Wire Line
	5350 2875 5350 3200
Wire Wire Line
	5450 2500 5450 2875
Wire Wire Line
	4125 1175 4475 1175
Wire Wire Line
	4125 1275 4325 1275
Wire Wire Line
	1750 4350 1750 4300
Wire Wire Line
	1750 3000 1750 3100
Wire Wire Line
	1600 3050 1750 3050
Connection ~ 1750 3050
Wire Wire Line
	1200 3050 1300 3050
Wire Wire Line
	2300 4000 2150 4000
Wire Wire Line
	2150 3900 2800 3900
Wire Wire Line
	2300 3800 2150 3800
Wire Wire Line
	2150 3700 2300 3700
Wire Wire Line
	2300 3600 2150 3600
Wire Wire Line
	2150 3500 2300 3500
Wire Wire Line
	2300 3400 2150 3400
Wire Wire Line
	8550 5100 8550 5200
Wire Wire Line
	8750 5050 8650 5050
Wire Wire Line
	8650 5050 8650 5150
Wire Wire Line
	8650 5150 8100 5150
Connection ~ 8550 5150
Wire Wire Line
	9150 5050 9050 5050
Wire Wire Line
	9000 5600 8950 5600
Wire Wire Line
	9000 5500 8950 5500
Wire Wire Line
	9000 5400 8950 5400
Wire Wire Line
	7600 5600 8150 5600
Wire Wire Line
	8100 5150 8100 5500
Wire Wire Line
	8100 5500 8150 5500
Wire Wire Line
	8150 5400 8100 5400
Connection ~ 8100 5400
Wire Wire Line
	8550 5850 8550 5800
Wire Wire Line
	4250 4800 4150 4800
Wire Wire Line
	2200 7000 2200 7100
Wire Wire Line
	1800 7300 1900 7300
Wire Wire Line
	2200 7600 2200 7500
Wire Wire Line
	7950 3950 7950 4150
Wire Wire Line
	8950 4500 8950 4450
Wire Wire Line
	7950 4500 7950 4450
Wire Wire Line
	8950 1600 9050 1600
Wire Wire Line
	9050 1600 9050 1550
Wire Wire Line
	8950 1700 9200 1700
Wire Wire Line
	9050 1700 9050 1750
Wire Wire Line
	9050 2150 9050 2050
Wire Wire Line
	9050 1150 9050 1250
Connection ~ 9050 1700
Wire Wire Line
	9300 1500 9200 1500
Wire Wire Line
	9200 1500 9200 1600
Wire Wire Line
	9200 1600 9150 1600
Wire Wire Line
	9150 1600 9150 1700
Connection ~ 9150 1700
Wire Wire Line
	9500 1700 9800 1700
Wire Wire Line
	9600 1700 9600 1800
Wire Wire Line
	9800 2150 9800 2050
Wire Wire Line
	9800 1600 9800 1750
Connection ~ 9600 1700
Connection ~ 9800 1700
Wire Wire Line
	9550 2250 9600 2250
Wire Wire Line
	9600 2250 9600 2100
Wire Wire Line
	3475 3400 3475 3525
Wire Wire Line
	3475 3775 3475 3725
Connection ~ 3475 3500
Wire Wire Line
	3475 3000 3475 3100
Wire Wire Line
	4100 4100 4250 4100
Wire Wire Line
	6900 4500 6650 4500
Wire Wire Line
	6750 4300 6650 4300
Wire Wire Line
	6800 4100 6650 4100
Wire Wire Line
	6900 4600 6650 4600
Wire Wire Line
	4050 5000 4250 5000
Wire Wire Line
	2800 3900 2800 3750
Wire Wire Line
	6950 4800 6650 4800
Wire Wire Line
	6800 3900 6650 3900
Wire Wire Line
	3075 1275 3000 1275
Wire Wire Line
	3000 1275 3000 1075
Wire Wire Line
	1850 7300 1850 7350
Connection ~ 1850 7300
Wire Wire Line
	1850 7700 1850 7650
Connection ~ 2850 6300
Wire Wire Line
	2850 5850 2850 5900
Wire Wire Line
	2800 3000 2800 3350
Wire Wire Line
	2800 3050 3100 3050
Wire Wire Line
	3100 3050 3100 3100
Connection ~ 2800 3050
Wire Wire Line
	3100 3400 3100 3550
Wire Wire Line
	3100 3550 3175 3550
Wire Wire Line
	6950 4900 6650 4900
Wire Wire Line
	2950 7100 2950 7200
Connection ~ 2950 6725
Text Label 4100 6950 2    60   ~ 0
Rsense
$Comp
L R R13
U 1 1 56FFA957
P 4300 6950
F 0 "R13" V 4380 6950 50  0000 C CNN
F 1 "4K7" V 4300 6950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4230 6950 50  0001 C CNN
F 3 "" H 4300 6950 50  0000 C CNN
	1    4300 6950
	0    1    1    0   
$EndComp
$Comp
L C C14
U 1 1 56FFB0C7
P 4500 7150
F 0 "C14" H 4500 7250 40  0000 L CNN
F 1 "10uF" H 4506 7065 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4538 7000 30  0001 C CNN
F 3 "" H 4500 7150 60  0000 C CNN
	1    4500 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 6950 4150 6950
Wire Wire Line
	4450 6950 4550 6950
Wire Wire Line
	4500 6950 4500 7000
$Comp
L GND #PWR044
U 1 1 56FFB973
P 4500 7350
F 0 "#PWR044" H 4500 7100 50  0001 C CNN
F 1 "GND" H 4500 7200 50  0000 C CNN
F 2 "" H 4500 7350 50  0000 C CNN
F 3 "" H 4500 7350 50  0000 C CNN
	1    4500 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 7350 4500 7300
Text Label 4550 6950 0    60   ~ 0
Vsense
Connection ~ 4500 6950
Text Label 3825 4600 0    60   ~ 0
Vsense
Wire Wire Line
	3825 4600 4250 4600
$EndSCHEMATC
