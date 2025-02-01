EESchema Schematic File Version 4
EELAYER 30 0
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
L RF:NRF24L01_Breakout U2
U 1 1 5FB8288C
P 6250 3750
F 0 "U2" H 6630 3796 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 6630 3705 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 6400 4350 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 6250 3650 50  0001 C CNN
	1    6250 3750
	1    0    0    -1  
$EndComp
$Comp
L STM:FT232H U1
U 1 1 5FB518D4
P 4600 2800
F 0 "U1" H 4575 2915 50  0000 C CNN
F 1 "FT232H" H 4575 2824 50  0000 C CNN
F 2 "Telemetry_receiver:AdafruitFT232HBreakout" H 4600 2800 50  0001 C CNN
F 3 "" H 4600 2800 50  0001 C CNN
	1    4600 2800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5750 3650 5500 3650
Wire Wire Line
	5500 3650 5500 3350
Wire Wire Line
	6650 3250 6650 4350
Wire Wire Line
	6650 4350 6250 4350
Wire Wire Line
	5750 3750 5400 3750
Wire Wire Line
	5400 3750 5400 3650
Wire Wire Line
	5750 3950 5300 3950
Wire Wire Line
	5300 3950 5300 3750
Wire Wire Line
	5750 4050 5200 4050
Wire Wire Line
	5200 4050 5200 3850
Wire Wire Line
	5050 3250 6000 3250
Wire Wire Line
	5050 3350 5500 3350
Wire Wire Line
	5050 3450 5750 3450
Wire Wire Line
	5050 3550 5750 3550
Wire Wire Line
	5050 3650 5400 3650
Wire Wire Line
	5050 3750 5300 3750
Wire Wire Line
	5050 3850 5200 3850
$Comp
L Device:C C100nF1
U 1 1 5FCD0678
P 6000 3100
F 0 "C100nF1" H 6115 3146 50  0000 L CNN
F 1 "C" H 6115 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6038 2950 50  0001 C CNN
F 3 "~" H 6000 3100 50  0001 C CNN
	1    6000 3100
	1    0    0    -1  
$EndComp
Connection ~ 6000 3250
Wire Wire Line
	6000 3250 6650 3250
Wire Wire Line
	6250 2950 6000 2950
Wire Wire Line
	5700 2950 5700 3050
Wire Wire Line
	5700 3050 5050 3050
Wire Wire Line
	6250 2950 6250 3150
Connection ~ 6000 2950
Wire Wire Line
	6000 2950 5700 2950
$EndSCHEMATC
