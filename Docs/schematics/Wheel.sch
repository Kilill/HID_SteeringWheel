EESchema Schematic File Version 4
LIBS:Wheel-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Wheel and Pedal USB conversion"
Date "2021-09-13"
Rev "1"
Comp "LIT"
Comment1 "Kim Lilliestierna"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_Push SW3
U 1 1 613E41F3
P 9100 3900
F 0 "SW3" H 9250 3950 50  0000 L CNN
F 1 "SW_Shift_Up" H 8900 4050 50  0000 L CNN
F 2 "" H 9100 4100 50  0001 C CNN
F 3 "~" H 9100 4100 50  0001 C CNN
	1    9100 3900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 613E5836
P 9100 4200
F 0 "SW4" H 9350 4250 50  0000 C CNN
F 1 "SW_Shift_Down" H 9100 4350 50  0000 C CNN
F 2 "" H 9100 4400 50  0001 C CNN
F 3 "~" H 9100 4400 50  0001 C CNN
	1    9100 4200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 613E6533
P 6100 5750
F 0 "SW2" H 6200 5800 50  0000 L CNN
F 1 "SW_Wheel_Right" H 5900 5950 50  0000 L CNN
F 2 "" H 6100 5950 50  0001 C CNN
F 3 "~" H 6100 5950 50  0001 C CNN
	1    6100 5750
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 613E6AC3
P 6100 5350
F 0 "SW1" H 6250 5400 50  0000 C CNN
F 1 "SW_Wheel_Left" H 6100 5550 50  0000 C CNN
F 2 "" H 6100 5550 50  0001 C CNN
F 3 "~" H 6100 5550 50  0001 C CNN
	1    6100 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV3
U 1 1 613E8048
P 6150 4500
F 0 "RV3" H 6050 4550 50  0000 R CNN
F 1 "120K" H 6050 4450 50  0000 R CNN
F 2 "" H 6150 4500 50  0001 C CNN
F 3 "~" H 6150 4500 50  0001 C CNN
	1    6150 4500
	1    0    0    1   
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 613EA2FB
P 3200 3450
F 0 "RV1" H 3000 3500 50  0000 C CNN
F 1 "100K" H 3000 3400 50  0000 C CNN
F 2 "" H 3200 3450 50  0001 C CNN
F 3 "~" H 3200 3450 50  0001 C CNN
	1    3200 3450
	1    0    0    1   
$EndComp
$Comp
L Device:R_POT RV2
U 1 1 613EB12F
P 3700 3250
F 0 "RV2" H 3600 3300 50  0000 R CNN
F 1 "100K" H 3600 3200 50  0000 R CNN
F 2 "" H 3700 3250 50  0001 C CNN
F 3 "~" H 3700 3250 50  0001 C CNN
	1    3700 3250
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6140232D
P 6250 3700
F 0 "#PWR04" H 6250 3450 50  0001 C CNN
F 1 "GND" H 6255 3527 50  0000 C CNN
F 2 "" H 6250 3700 50  0001 C CNN
F 3 "" H 6250 3700 50  0001 C CNN
	1    6250 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 61418903
P 6150 4650
F 0 "#PWR02" H 6150 4400 50  0001 C CNN
F 1 "GND" H 6155 4477 50  0000 C CNN
F 2 "" H 6150 4650 50  0001 C CNN
F 3 "" H 6150 4650 50  0001 C CNN
	1    6150 4650
	1    0    0    -1  
$EndComp
$Comp
L DigisparkMode:DigisparkPro U1
U 1 1 6140EC2C
P 8000 3650
F 0 "U1" H 7775 4465 50  0000 C CNN
F 1 "DigisparkPro" H 7775 4374 50  0000 C CNN
F 2 "" H 8000 3650 50  0001 C CNN
F 3 "" H 8000 3650 50  0001 C CNN
	1    8000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3300 7100 3300
Wire Wire Line
	6100 3550 6250 3550
Wire Wire Line
	6250 3550 6250 3700
$Comp
L power:+5V #PWR03
U 1 1 61422909
P 6200 3350
F 0 "#PWR03" H 6200 3200 50  0001 C CNN
F 1 "+5V" V 6200 3550 50  0000 C CNN
F 2 "" H 6200 3350 50  0001 C CNN
F 3 "" H 6200 3350 50  0001 C CNN
	1    6200 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 3350 6200 3350
$Comp
L Connector:RJ9 J1
U 1 1 61424B41
P 4500 3350
F 0 "J1" H 4170 3354 50  0000 R CNN
F 1 "RJ9" H 4170 3445 50  0000 R CNN
F 2 "SparkFun-Connectors:RJ9" V 4500 3400 50  0001 C CNN
F 3 "~" V 4500 3400 50  0001 C CNN
	1    4500 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	6700 3250 6700 3300
Wire Wire Line
	6100 3250 6700 3250
Wire Wire Line
	4100 3250 3850 3250
Wire Wire Line
	3200 3750 3700 3750
Wire Wire Line
	3350 3450 4100 3450
Wire Wire Line
	3200 3600 3200 3750
Wire Wire Line
	3950 3350 4100 3350
Text Notes 6800 3300 0    50   ~ 0
Break
Text Notes 8450 3450 0    50   ~ 0
Accell
Text Notes 4100 3450 2    50   ~ 0
Accell
Text Notes 4100 3250 2    50   ~ 0
Break
Wire Wire Line
	6300 4500 6350 4500
Wire Wire Line
	6350 4500 6350 3600
Text Notes 6800 3600 0    50   ~ 0
Wheel
Wire Wire Line
	5900 5350 5900 5750
$Comp
L power:GND #PWR01
U 1 1 6146C6B9
P 5900 5750
F 0 "#PWR01" H 5900 5500 50  0001 C CNN
F 1 "GND" H 5905 5577 50  0000 C CNN
F 2 "" H 5900 5750 50  0001 C CNN
F 3 "" H 5900 5750 50  0001 C CNN
	1    5900 5750
	1    0    0    -1  
$EndComp
Connection ~ 5900 5750
Wire Wire Line
	6300 5350 6500 5350
Wire Wire Line
	6500 5350 6500 3750
Wire Wire Line
	6300 5750 6600 5750
Wire Wire Line
	6600 5750 6600 3900
Wire Wire Line
	8900 3900 8450 3900
Wire Wire Line
	9300 3900 9300 4200
$Comp
L power:GND #PWR06
U 1 1 614733A2
P 9300 4350
F 0 "#PWR06" H 9300 4100 50  0001 C CNN
F 1 "GND" H 9305 4177 50  0000 C CNN
F 2 "" H 9300 4350 50  0001 C CNN
F 3 "" H 9300 4350 50  0001 C CNN
	1    9300 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 3600 7100 3600
Wire Wire Line
	6500 3750 7100 3750
Wire Wire Line
	6600 3900 7100 3900
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 61479264
P 6750 4050
F 0 "J3" H 6858 4231 50  0000 C CNN
F 1 "TX/RX" H 6858 4140 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Vertical" H 6750 4050 50  0001 C CNN
F 3 "~" H 6750 4050 50  0001 C CNN
	1    6750 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4050 6950 4050
Wire Wire Line
	6950 4150 7100 4150
Wire Wire Line
	7100 4150 7100 4200
Wire Notes Line
	5000 2500 5000 3950
Wire Notes Line
	5000 3950 2750 3950
Wire Notes Line
	2750 3950 2750 2500
Wire Notes Line
	2750 2500 5000 2500
Wire Notes Line
	5200 2500 5200 6150
Wire Notes Line
	5200 6150 9550 6150
Wire Notes Line
	9550 6150 9550 2500
Wire Notes Line
	9550 2500 5200 2500
Text Notes 3400 2400 0    50   ~ 0
Pedal Assembly\n
Text Notes 7050 2450 0    50   ~ 0
Wheel Assmebly
Wire Wire Line
	6100 3450 6600 3450
Wire Wire Line
	6600 3450 6600 2800
Wire Wire Line
	6600 2800 8800 2800
Wire Wire Line
	8800 2800 8800 3450
Wire Wire Line
	8800 3450 8450 3450
Connection ~ 9300 4200
Wire Wire Line
	9300 4200 9300 4350
Wire Wire Line
	8900 4200 8450 4200
Text GLabel 8450 4350 2    50   Input ~ 0
+5V
Text GLabel 7100 4350 0    50   Input ~ 0
+5V
$Comp
L power:GND #PWR05
U 1 1 6148E8D4
P 8550 3300
F 0 "#PWR05" H 8550 3050 50  0001 C CNN
F 1 "GND" H 8555 3127 50  0000 C CNN
F 2 "" H 8550 3300 50  0001 C CNN
F 3 "" H 8550 3300 50  0001 C CNN
	1    8550 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8550 3300 8450 3300
NoConn ~ 8450 4050
NoConn ~ 8450 3150
NoConn ~ 7950 4650
NoConn ~ 7800 4650
NoConn ~ 7650 4650
$Comp
L Connector:RJ9 J2
U 1 1 61492A83
P 5700 3350
F 0 "J2" H 5370 3354 50  0000 R CNN
F 1 "RJ9" H 5370 3445 50  0000 R CNN
F 2 "SparkFun-Connectors:RJ9" V 5700 3400 50  0001 C CNN
F 3 "~" V 5700 3400 50  0001 C CNN
	1    5700 3350
	1    0    0    1   
$EndComp
Text Notes 4100 3350 2    50   ~ 0
+5V
Text Notes 4100 3550 2    50   ~ 0
GND
Wire Wire Line
	3700 3100 3700 3050
Wire Wire Line
	3700 3050 3950 3050
Wire Wire Line
	3950 3050 3950 3350
Wire Wire Line
	3700 3050 3200 3050
Wire Wire Line
	3200 3050 3200 3300
Connection ~ 3700 3050
Wire Wire Line
	3700 3400 3700 3750
Wire Wire Line
	4100 3550 4050 3550
Wire Wire Line
	4050 3550 4050 3750
Wire Wire Line
	4050 3750 3700 3750
Connection ~ 3700 3750
NoConn ~ 8450 3600
NoConn ~ 8450 3750
Text Notes 8500 3700 0    50   ~ 0
USB
$Comp
L power:+5V #PWR?
U 1 1 6149E9B3
P 6150 4350
F 0 "#PWR?" H 6150 4200 50  0001 C CNN
F 1 "+5V" V 6150 4550 50  0000 C CNN
F 2 "" H 6150 4350 50  0001 C CNN
F 3 "" H 6150 4350 50  0001 C CNN
	1    6150 4350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
