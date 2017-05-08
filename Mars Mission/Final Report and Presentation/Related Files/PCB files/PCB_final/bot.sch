EESchema Schematic File Version 2
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
LIBS:SparkFun
LIBS:bot-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Battery BT1
U 1 1 58FA899C
P 5500 2650
F 0 "BT1" H 5600 2750 50  0000 L CNN
F 1 "Battery" H 5600 2650 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x01_Pitch2.54mm" V 5500 2710 50  0001 C CNN
F 3 "" V 5500 2710 50  0001 C CNN
	1    5500 2650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 J3
U 1 1 58FBAEEF
P 5150 1300
F 0 "J3" H 5150 1500 50  0000 C CNN
F 1 "IR sensor" V 5250 1300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 5150 1300 50  0001 C CNN
F 3 "" H 5150 1300 50  0001 C CNN
	1    5150 1300
	0    -1   -1   0   
$EndComp
Text Label 5750 2150 0    40   ~ 0
GND
Text Label 5750 2050 0    40   ~ 0
12
Text Label 5750 1950 0    40   ~ 0
11
Text Label 5750 1850 0    40   ~ 0
10
Text Label 5750 1750 0    40   ~ 0
9
$Comp
L CONN_01X06 J1
U 1 1 58FBABD4
P 4250 1650
F 0 "J1" H 4250 2000 50  0000 C CNN
F 1 "L298" V 4350 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 4250 1650 50  0001 C CNN
F 3 "" H 4250 1650 50  0001 C CNN
	1    4250 1650
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X01 J5
U 1 1 58FE1AC8
P 6000 1650
F 0 "J5" H 6000 1750 50  0000 C CNN
F 1 "Vin (5V)" V 6100 1650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 6000 1650 50  0001 C CNN
F 3 "" H 6000 1650 50  0001 C CNN
	1    6000 1650
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 2350 5800 2850
Wire Wire Line
	4300 2050 5450 2050
Wire Wire Line
	4400 1950 5450 1950
Wire Wire Line
	4500 1850 5450 1850
Wire Wire Line
	5450 2150 5350 2150
Wire Wire Line
	5500 2400 5500 2450
Wire Wire Line
	6350 2300 4200 2300
Wire Wire Line
	4100 2350 5800 2350
Wire Wire Line
	4000 2400 5500 2400
Wire Wire Line
	4400 1850 4400 1950
Wire Wire Line
	4300 1850 4300 2050
Wire Wire Line
	4000 1850 4000 2400
Wire Wire Line
	4100 1850 4100 2350
Wire Wire Line
	4200 2300 4200 1850
Wire Wire Line
	6350 850  6350 2300
Wire Wire Line
	5350 2150 5350 2350
Connection ~ 5350 2350
Wire Wire Line
	5450 1750 5250 1750
Wire Wire Line
	5250 1750 5250 1500
Wire Wire Line
	5150 1500 5150 2350
Connection ~ 5150 2350
Wire Wire Line
	5050 1500 5050 2300
Connection ~ 5050 2300
Wire Wire Line
	5800 2850 5500 2850
$Comp
L CONN_01X07 J2
U 1 1 58FF9B2F
P 5650 1850
F 0 "J2" H 5650 2250 50  0000 C CNN
F 1 "CONN_01X07" V 5750 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 5650 1850 50  0001 C CNN
F 3 "" H 5650 1850 50  0001 C CNN
	1    5650 1850
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 J4
U 1 1 58FF9B85
P 5700 1100
F 0 "J4" H 5700 1300 50  0000 C CNN
F 1 "limit1" V 5800 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 5700 1100 50  0001 C CNN
F 3 "" H 5700 1100 50  0001 C CNN
	1    5700 1100
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 J6
U 1 1 58FF9C4E
P 6150 1100
F 0 "J6" H 6150 1300 50  0000 C CNN
F 1 "limit2" V 6250 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6150 1100 50  0001 C CNN
F 3 "" H 6150 1100 50  0001 C CNN
	1    6150 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5600 1300 5400 1300
Wire Wire Line
	5400 1300 5400 1650
Wire Wire Line
	5400 1650 5450 1650
Wire Wire Line
	6050 1300 6050 1400
Wire Wire Line
	6050 1400 5450 1400
Wire Wire Line
	5450 1400 5450 1550
Wire Wire Line
	6250 1300 6350 1300
Connection ~ 6350 1650
Wire Wire Line
	5800 1300 5900 1300
Wire Wire Line
	5900 1300 5900 850 
Wire Wire Line
	5900 850  6350 850 
Connection ~ 6350 1300
Wire Wire Line
	6150 1300 6150 2250
Wire Wire Line
	6150 2250 5350 2250
Connection ~ 5350 2250
Wire Wire Line
	5700 1300 5700 1350
Wire Wire Line
	5700 1350 6150 1350
Connection ~ 6150 1350
Wire Wire Line
	6350 1650 6200 1650
$EndSCHEMATC
