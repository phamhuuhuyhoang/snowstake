EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END

$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Snowstake"
Date "2021-05-06"
Rev "0.1"

Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr

$Comp
L RF_Module:PHOTON-MCU_Module U1
U 1 1 6090B6A3
P 2250 2900
F 0 "U1" H 2250 1961 50  0000 C CNN
F 1 "PHOTON-MCU_Module" H 2250 1870 50  0000 C CNN
F 2 "RF_Module:photon_tht" H 2600 1950 50  0001 C CNN
F 3 "https://docs.particle.io/datasheets/wi-fi/photon-datasheet/" H 2600 1950 50  0001 C CNN
	1    2250 2900
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR04
U 1 1 60936F42
P 2350 4050
F 0 "#PWR04" H 2350 3800 50  0001 C CNN
F 1 "GND" H 2355 3877 50  0000 C CNN
F 2 "" H 2350 4050 50  0001 C CNN
F 3 "" H 2350 4050 50  0001 C CNN
	1    2350 4050
	1    0    0    -1  
$EndComp


Wire Wire Line
	2350 3750 2350 4050
Wire Wire Line
	2150 3750 2350 3750
Connection ~ 2350 3750

$Comp
L power:+5V #PWR02
U 1 1 60937312
P 2050 1750
F 0 "#PWR02" H 2050 1600 50  0001 C CNN
F 1 "+5V" H 2065 1923 50  0000 C CNN
F 2 "" H 2050 1750 50  0001 C CNN
F 3 "" H 2050 1750 50  0001 C CNN
	1    2050 1750
	1    0    0    -1  
$EndComp

Wire Wire Line
	2050 1750 2050 1950

$Comp
L Transistor_FET:BSS138 Q2
U 1 1 60937AF5
P 7750 1850
F 0 "Q2" V 7999 1850 50  0000 C CNN
F 1 "BSS138" V 8090 1850 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7950 1775 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 7750 1850 50  0001 L CNN
	1    7750 1850
	0    1    1    0   
$EndComp

$Comp
L Device:R R6
U 1 1 6093A920
P 7300 1600
F 0 "R6" H 7370 1646 50  0000 L CNN
F 1 "4.99k" H 7370 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7230 1600 50  0001 C CNN
F 3 "~" H 7300 1600 50  0001 C CNN
	1    7300 1600
	1    0    0    -1  
$EndComp

$Comp
L Device:R R9
U 1 1 6093B309
P 8200 1600
F 0 "R9" H 8270 1646 50  0000 L CNN
F 1 "4.99k" H 8270 1555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8130 1600 50  0001 C CNN
F 3 "~" H 8200 1600 50  0001 C CNN
	1    8200 1600
	1    0    0    -1  
$EndComp

$Comp
L power:+5V #PWR015
U 1 1 6093D088
P 8200 1300
F 0 "#PWR015" H 8200 1150 50  0001 C CNN
F 1 "+5V" H 8215 1473 50  0000 C CNN
F 2 "" H 8200 1300 50  0001 C CNN
F 3 "" H 8200 1300 50  0001 C CNN
	1    8200 1300
	1    0    0    -1  
$EndComp

$Comp
L power:+3.3V #PWR012
U 1 1 6093D64F
P 7300 1300
F 0 "#PWR012" H 7300 1150 50  0001 C CNN
F 1 "+3.3V" H 7315 1473 50  0000 C CNN
F 2 "" H 7300 1300 50  0001 C CNN
F 3 "" H 7300 1300 50  0001 C CNN
	1    7300 1300
	1    0    0    -1  
$EndComp

$Comp
L power:+3.3V #PWR03
U 1 1 6093DF37
P 2250 1900
F 0 "#PWR03" H 2250 1750 50  0001 C CNN
F 1 "+3.3V" H 2265 2073 50  0000 C CNN
F 2 "" H 2250 1900 50  0001 C CNN
F 3 "" H 2250 1900 50  0001 C CNN
	1    2250 1900
	1    0    0    -1  
$EndComp

Wire Wire Line
	7300 1300 7300 1400
Wire Wire Line
	7750 1650 7750 1400
Wire Wire Line
	7750 1400 7300 1400
Connection ~ 7300 1400
Wire Wire Line
	7300 1400 7300 1450
Wire Wire Line
	7300 1750 7300 1950
Wire Wire Line
	7300 1950 7550 1950
Wire Wire Line
	7950 1950 8200 1950
Wire Wire Line
	8200 1950 8200 1750
Wire Wire Line
	8200 1450 8200 1300
Wire Wire Line
	2250 1900 2250 2000
NoConn ~ 2450 2200

$Comp
L Device:C C1
U 1 1 6093F3AB
P 1700 1950
F 0 "C1" V 1448 1950 50  0000 C CNN
F 1 "0.1uF" V 1539 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1738 1800 50  0001 C CNN
F 3 "~" H 1700 1950 50  0001 C CNN
	1    1700 1950
	0    1    1    0   
$EndComp

$Comp
L Device:C C2
U 1 1 6093FC81
P 2600 2000
F 0 "C2" V 2348 2000 50  0000 C CNN
F 1 "0.1uF" V 2439 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2638 1850 50  0001 C CNN
F 3 "~" H 2600 2000 50  0001 C CNN
	1    2600 2000
	0    1    1    0   
$EndComp

$Comp
L power:GND #PWR05
U 1 1 60940176
P 2750 2000
F 0 "#PWR05" H 2750 1750 50  0001 C CNN
F 1 "GND" H 2755 1827 50  0000 C CNN
F 2 "" H 2750 2000 50  0001 C CNN
F 3 "" H 2750 2000 50  0001 C CNN
	1    2750 2000
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR01
U 1 1 6094080D
P 1550 1950
F 0 "#PWR01" H 1550 1700 50  0001 C CNN
F 1 "GND" H 1555 1777 50  0000 C CNN
F 2 "" H 1550 1950 50  0001 C CNN
F 3 "" H 1550 1950 50  0001 C CNN
	1    1550 1950
	1    0    0    -1  
$EndComp

Wire Wire Line
	1850 1950 2050 1950
Connection ~ 2050 1950
Wire Wire Line
	2050 1950 2050 2200
Wire Wire Line
	2450 2000 2250 2000
Connection ~ 2250 2000
Wire Wire Line
	2250 2000 2250 2200
Wire Wire Line
	2750 3000 3100 3000
Text Label 6850 1950 0    50   ~ 0
D6
Wire Wire Line
	7300 1950 6850 1950
Connection ~ 7300 1950
Wire Wire Line
	8200 1950 8750 1950
Connection ~ 8200 1950
Text Label 8300 1950 0    50   ~ 0
DIN

$Comp
L Device:C C3
U 1 1 60942B64
P 10050 1550
F 0 "C3" H 10165 1596 50  0000 L CNN
F 1 "10uF" H 10165 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 10088 1400 50  0001 C CNN
F 3 "~" H 10050 1550 50  0001 C CNN
	1    10050 1550
	1    0    0    -1  
$EndComp

$Comp
L power:+5V #PWR018
U 1 1 609436E6
P 10050 1300
F 0 "#PWR018" H 10050 1150 50  0001 C CNN
F 1 "+5V" H 10065 1473 50  0000 C CNN
F 2 "" H 10050 1300 50  0001 C CNN
F 3 "" H 10050 1300 50  0001 C CNN
	1    10050 1300
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR019
U 1 1 60943E01
P 10050 1850
F 0 "#PWR019" H 10050 1600 50  0001 C CNN
F 1 "GND" H 10055 1677 50  0000 C CNN
F 2 "" H 10050 1850 50  0001 C CNN
F 3 "" H 10050 1850 50  0001 C CNN
	1    10050 1850
	1    0    0    -1  
$EndComp

Wire Wire Line
	10050 1300 10050 1400
Wire Wire Line
	10050 1700 10050 1850

$Comp
L Device:LED D1
U 1 1 60944C11
P 5250 4600
F 0 "D1" V 5289 4482 50  0000 R CNN
F 1 "LED" V 5198 4482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 5250 4600 50  0001 C CNN
F 3 "~" H 5250 4600 50  0001 C CNN
	1    5250 4600
	0    -1   -1   0   
$EndComp

$Comp
L Device:LED D2
U 1 1 6094568F
P 5850 4600
F 0 "D2" V 5889 4482 50  0000 R CNN
F 1 "LED" V 5798 4482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 5850 4600 50  0001 C CNN
F 3 "~" H 5850 4600 50  0001 C CNN
	1    5850 4600
	0    -1   -1   0   
$EndComp

$Comp
L Device:LED D3
U 1 1 60946793
P 6450 4600
F 0 "D3" V 6489 4482 50  0000 R CNN
F 1 "LED" V 6398 4482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6450 4600 50  0001 C CNN
F 3 "~" H 6450 4600 50  0001 C CNN
	1    6450 4600
	0    -1   -1   0   
$EndComp

$Comp
L Device:LED D4
U 1 1 60946E6E
P 7000 4600
F 0 "D4" V 7039 4482 50  0000 R CNN
F 1 "LED" V 6948 4482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 7000 4600 50  0001 C CNN
F 3 "~" H 7000 4600 50  0001 C CNN
	1    7000 4600
	0    -1   -1   0   
$EndComp

$Comp
L Device:LED D5
U 1 1 6094738B
P 7500 4600
F 0 "D5" V 7539 4482 50  0000 R CNN
F 1 "LED" V 7448 4482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 7500 4600 50  0001 C CNN
F 3 "~" H 7500 4600 50  0001 C CNN
	1    7500 4600
	0    -1   -1   0   
$EndComp

$Comp
L Device:LED D6
U 1 1 60947CD5
P 7950 4600
F 0 "D6" V 7989 4482 50  0000 R CNN
F 1 "LED" V 7898 4482 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 7950 4600 50  0001 C CNN
F 3 "~" H 7950 4600 50  0001 C CNN
	1    7950 4600
	0    -1   -1   0   
$EndComp

$Comp
L Device:R R2
U 1 1 6094A29E
P 5250 4300
F 0 "R2" H 5320 4346 50  0000 L CNN
F 1 "499" H 5320 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5180 4300 50  0001 C CNN
F 3 "~" H 5250 4300 50  0001 C CNN
	1    5250 4300
	1    0    0    -1  
$EndComp

$Comp
L Device:R R3
U 1 1 6094A9A5
P 5850 4300
F 0 "R3" H 5920 4346 50  0000 L CNN
F 1 "499" H 5920 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5780 4300 50  0001 C CNN
F 3 "~" H 5850 4300 50  0001 C CNN
	1    5850 4300
	1    0    0    -1  
$EndComp

$Comp
L Device:R R4
U 1 1 6094AE61
P 6450 4300
F 0 "R4" H 6520 4346 50  0000 L CNN
F 1 "499" H 6520 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6380 4300 50  0001 C CNN
F 3 "~" H 6450 4300 50  0001 C CNN
	1    6450 4300
	1    0    0    -1  
$EndComp

$Comp
L Device:R R5
U 1 1 6094B3E1
P 7000 4300
F 0 "R5" H 7070 4346 50  0000 L CNN
F 1 "499" H 7070 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6930 4300 50  0001 C CNN
F 3 "~" H 7000 4300 50  0001 C CNN
	1    7000 4300
	1    0    0    -1  
$EndComp

$Comp
L Device:R R7
U 1 1 6094BCCE
P 7500 4300
F 0 "R7" H 7570 4346 50  0000 L CNN
F 1 "499" H 7570 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7430 4300 50  0001 C CNN
F 3 "~" H 7500 4300 50  0001 C CNN
	1    7500 4300
	1    0    0    -1  
$EndComp

$Comp
L Device:R R8
U 1 1 6094C047
P 7950 4300
F 0 "R8" H 8020 4346 50  0000 L CNN
F 1 "499" H 8020 4255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7880 4300 50  0001 C CNN
F 3 "~" H 7950 4300 50  0001 C CNN
	1    7950 4300
	1    0    0    -1  
$EndComp

Text Label 2950 3200 0    50   ~ 0
D0
Text Label 2950 3100 0    50   ~ 0
D1
Text Label 2950 2900 0    50   ~ 0
D3
Text Label 2950 2800 0    50   ~ 0
D4
Text Label 2950 2700 0    50   ~ 0
D5
Text Label 2950 2600 0    50   ~ 0
D6
Text Label 2950 2500 0    50   ~ 0
D7
Wire Wire Line
	2750 3100 3050 3100
Wire Wire Line
	2750 3200 3100 3200
Wire Wire Line
	2750 2900 3100 2900
Wire Wire Line
	2750 2800 3100 2800
Wire Wire Line
	2750 2700 3100 2700
Wire Wire Line
	2750 2600 3100 2600
Wire Wire Line
	2750 2500 3100 2500

$Comp
L Connector:TestPoint TP1
U 1 1 609A69E8
P 8750 1700
F 0 "TP1" V 8704 1888 50  0000 L CNN
F 1 "TestPoint" V 8795 1888 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_4.0x4.0mm" H 8950 1700 50  0001 C CNN
F 3 "~" H 8950 1700 50  0001 C CNN
	1    8750 1700
	0    1    1    0   
$EndComp

$Comp
L Connector:TestPoint TP2
U 1 1 609A758C
P 8750 1950
F 0 "TP2" V 8704 2138 50  0000 L CNN
F 1 "TestPoint" V 8795 2138 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_4.0x4.0mm" H 8950 1950 50  0001 C CNN
F 3 "~" H 8950 1950 50  0001 C CNN
	1    8750 1950
	0    1    1    0   
$EndComp

$Comp
L Connector:TestPoint TP3
U 1 1 609A8ADC
P 8750 2200
F 0 "TP3" V 8704 2388 50  0000 L CNN
F 1 "TestPoint" V 8795 2388 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_4.0x4.0mm" H 8950 2200 50  0001 C CNN
F 3 "~" H 8950 2200 50  0001 C CNN
	1    8750 2200
	0    1    1    0   
$EndComp

$Comp
L power:GND #PWR017
U 1 1 609AA339
P 8750 2200
F 0 "#PWR017" H 8750 1950 50  0001 C CNN
F 1 "GND" H 8755 2027 50  0000 C CNN
F 2 "" H 8750 2200 50  0001 C CNN
F 3 "" H 8750 2200 50  0001 C CNN
	1    8750 2200
	1    0    0    -1  
$EndComp

$Comp
L power:+5V #PWR016
U 1 1 609AB040
P 8750 1700
F 0 "#PWR016" H 8750 1550 50  0001 C CNN
F 1 "+5V" H 8765 1873 50  0000 C CNN
F 2 "" H 8750 1700 50  0001 C CNN
F 3 "" H 8750 1700 50  0001 C CNN
	1    8750 1700
	1    0    0    -1  
$EndComp
Text Label 2950 3000 0    50   ~ 0
D2
Wire Wire Line
	5850 4750 5850 4850
Wire Wire Line
	6450 4750 6450 4850
Wire Wire Line
	7000 4750 7000 4850
Wire Wire Line
	7500 4750 7500 4850
Wire Wire Line
	7950 4750 7950 4850
$Comp
L Mechanical:Fiducial FID1
U 1 1 6098AFE1
P 10050 3450
F 0 "FID1" H 10135 3496 50  0000 L CNN
F 1 "Fiducial" H 10135 3405 50  0000 L CNN
F 2 "Fiducial:Fiducial_0.75mm_Mask1.5mm" H 10050 3450 50  0001 C CNN
F 3 "~" H 10050 3450 50  0001 C CNN
	1    10050 3450
	1    0    0    -1  
$EndComp

$Comp
L Mechanical:Fiducial FID2
U 1 1 6098B69D
P 10050 3800
F 0 "FID2" H 10135 3846 50  0000 L CNN
F 1 "Fiducial" H 10135 3755 50  0000 L CNN
F 2 "Fiducial:Fiducial_0.75mm_Mask1.5mm" H 10050 3800 50  0001 C CNN
F 3 "~" H 10050 3800 50  0001 C CNN
	1    10050 3800
	1    0    0    -1  
$EndComp

$Comp
L Mechanical:Fiducial FID3
U 1 1 6098C3CA
P 10050 4150
F 0 "FID3" H 10135 4196 50  0000 L CNN
F 1 "Fiducial" H 10135 4105 50  0000 L CNN
F 2 "Fiducial:Fiducial_0.75mm_Mask1.5mm" H 10050 4150 50  0001 C CNN
F 3 "~" H 10050 4150 50  0001 C CNN
	1    10050 4150
	1    0    0    -1  
$EndComp

$Comp
L Mechanical:MountingHole H1
U 1 1 6098E440
P 9100 3450
F 0 "H1" H 9200 3496 50  0000 L CNN
F 1 "MountingHole" H 9200 3405 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.1mm" H 9100 3450 50  0001 C CNN
F 3 "~" H 9100 3450 50  0001 C CNN
	1    9100 3450
	1    0    0    -1  
$EndComp

$Comp
L Mechanical:MountingHole H2
U 1 1 6098E7A0
P 9100 3800
F 0 "H2" H 9200 3846 50  0000 L CNN
F 1 "MountingHole" H 9200 3755 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.1mm" H 9100 3800 50  0001 C CNN
F 3 "~" H 9100 3800 50  0001 C CNN
	1    9100 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4750 5250 4900
$Comp
L power:GND #PWR0101
U 1 1 60B7B152
P 5250 4900
F 0 "#PWR0101" H 5250 4650 50  0001 C CNN
F 1 "GND" H 5255 4727 50  0000 C CNN
F 2 "" H 5250 4900 50  0001 C CNN
F 3 "" H 5250 4900 50  0001 C CNN
	1    5250 4900
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR0102
U 1 1 60B7BBB9
P 5850 4850
F 0 "#PWR0102" H 5850 4600 50  0001 C CNN
F 1 "GND" H 5855 4677 50  0000 C CNN
F 2 "" H 5850 4850 50  0001 C CNN
F 3 "" H 5850 4850 50  0001 C CNN
	1    5850 4850
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR0103
U 1 1 60B7C1B1
P 6450 4850
F 0 "#PWR0103" H 6450 4600 50  0001 C CNN
F 1 "GND" H 6455 4677 50  0000 C CNN
F 2 "" H 6450 4850 50  0001 C CNN
F 3 "" H 6450 4850 50  0001 C CNN
	1    6450 4850
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR0104
U 1 1 60B7C82D
P 7000 4850
F 0 "#PWR0104" H 7000 4600 50  0001 C CNN
F 1 "GND" H 7005 4677 50  0000 C CNN
F 2 "" H 7000 4850 50  0001 C CNN
F 3 "" H 7000 4850 50  0001 C CNN
	1    7000 4850
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR0105
U 1 1 60B7CC80
P 7500 4850
F 0 "#PWR0105" H 7500 4600 50  0001 C CNN
F 1 "GND" H 7505 4677 50  0000 C CNN
F 2 "" H 7500 4850 50  0001 C CNN
F 3 "" H 7500 4850 50  0001 C CNN
	1    7500 4850
	1    0    0    -1  
$EndComp

$Comp
L power:GND #PWR0106
U 1 1 60B7D634
P 7950 4850
F 0 "#PWR0106" H 7950 4600 50  0001 C CNN
F 1 "GND" H 7955 4677 50  0000 C CNN
F 2 "" H 7950 4850 50  0001 C CNN
F 3 "" H 7950 4850 50  0001 C CNN
	1    7950 4850
	1    0    0    -1  
$EndComp

Text Label 5250 4050 0    50   ~ 0
D0
Text Label 5850 4050 0    50   ~ 0
D1
Text Label 6450 4050 0    50   ~ 0
D2
Text Label 7000 4050 0    50   ~ 0
D3
Text Label 7500 4050 0    50   ~ 0
D4
Text Label 7950 4050 0    50   ~ 0
D5
Wire Wire Line
	5250 4150 5250 4050
Wire Wire Line
	5850 4150 5850 4050
Wire Wire Line
	6450 4150 6450 4050
Wire Wire Line
	7000 4150 7000 4050
Wire Wire Line
	7500 4150 7500 4050
Wire Wire Line
	7950 4150 7950 4050
$EndSCHEMATC
