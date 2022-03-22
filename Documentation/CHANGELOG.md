# ChangeLog


#### 04/02/2022
As per discussion 26/01/22
1. Changed per channel 5v MOSFET switches to MOSFET control of DC/DC module on/off pin - due to failure of MOSFET switching during testing.
2. Added 5v buck converter for independent MCU_5V power bus.
	- Ensured all 5v MCU hardware is powered from common MCU_5V bus.
3. Removed circuit from NC pins on DC/DC modules.
4. Changed ESP32 USB interface to CH340
5. Changed MCU serial logic level converters from MOSFET to IC - TXS0102DCT
	- TODO: OE pin now requires low signal untill DC/DC supply is stable - Does it? Can it just be tied to 5v bus with a large capacitor? Does it need MCU to hold pin low untill 5V_BUS is stable?
6. Removed redundent 3V3_IN to power distribution page.
	- Rechecked all sheets for redundent pins, it won't impact drawing traces, but it will impact readability.
7. Added Mechanical layer as hirarchical sheet.
8. Moved voltage monitoring circuits to hirarchical sheet
9. Added voltage monitoring with TL431DBZ to 12V_BUS
10. Automatic shutoff circuit removed, as this would prevent the DC/DC module from powering on. Instead moved to AtMega328p digital inputs
and microcontroller will control shutdown of DC/DC supply if out of spec voltage detected.
		- This is a severe limitation compared to the specification, and this also does not prevent damage to devices on 5V_BUS if voltage is pulled high, for example to 12v due to user error.
		-  Add independent overvoltage protection to 5V_BUS? < No reasons for decision below [^1]
		[Zener Diode Overvoltage Protection - Sparkfun](https://www.rs-online.com/designspark/how-does-zener-diode-do-overvoltage-protection-in-circuit#:~:text=In%20order%20to%20protect%20the,flow%20in%20the%20reverse%20direction).
11. Changed logic level conversion for 12v outputs to 12v drive circuit. [12v drive circuit](https://forum.arduino.cc/t/easiest-way-of-driving-amplifying-from-5v-to-12v/123290)
12. Added proto pin connections for ESP MCU.
13. Changed 20v Zener in reverse voltage protection to 18v

#### 16/02/2022
14. Added Nominal Voltage indication for 5v & 12v Bus
15. Added capacitor to OE pin on logic level converter and tied pin to 3v3

#### 22/02/22
16. Changed logic level conversion circuit based on pspice analysis of previous circuit.

#### 23/02/2022

17. Reevaluated board with both microcontrollers on daughterboard. This is unfortunatly still not going to fit, however, by moving the AtMega & Associated hardware back onto the main PCB, it might free up enough space to fit the ESP32 as a breakaway module.


#### 24/02/2022

18. Changed power MOSFETs for dc/dc on/off control for logic level SOT-23 devices to save PCB space.
19. Successfuly reconfigured board with AtMega MCU on main board, and ESP for wifi functions on removeable module. [^daughterboard]

#### 02/03/2022

20. Changed 5V power to ACS712 from 5V_BUS to MCU_5v.
21. Increased size of 12v bus to 6.5mm for <20degC heating at 20A
22. Increased size of 5v bus to 4.8mm for <20degC heating at 16A
23. Changed GND pad connections to GND plane to solid
24. Changed hirachical sheets to include GNDPWR and GND. This make it easier to route different connections using different netclasses to account for different current requirements 
for each trace. This system seems very imperfect, but I cannot find another workaround.
25 changed clearance for 12V_BUS and GNDPWR from 0.2mm to 0.1985 - Difference seems negligable but passes DRC.

KiCAD feature suggestion - Net Class Labels. I would like to be able to specifiy that 2 nets are joined at any point, but apply different rules on different parts of the net.
Current workaround - Manually change the thickness of the traces after routing. Downside: time, care needed., DRC checks? 



### 28/04/2022 DESIGN REVIEW TODO:

Look up thermal management high current pin connections to GND plane

increase track width 7mm for 20degC temp rise with 0.035  @ 20A

24V bus rate for 35A


5v bus make sure rated for 15A  @20degC rise


practicable io logo

signature

get quote from JLC & PCB way


##### TODO:



	
	





## Change Notes




[^1]: Add independent overvoltage protection to 5V_BUS? 		[Zener Diode Overvoltage Protection - Sparkfun](https://www.rs-online.com/designspark/how-does-zener-diode-do-overvoltage-protection-in-circuit#:~:text=In%20order%20to%20protect%20the,flow%20in%20the%20reverse%20direction).
PROBLEM: Suggested 100r resistor between 5v and raspberry pi, this limits current to 50mA, raspi requires min 400mA (Tested with raspi 512mb, raspi4 will likely require more current) 
if R=12.5 is selected, Imax would be 400mA, however power disspation in the resistor is now 0.4\*5 = 2W.


[^daughterboard]: Board is too overloaded to fit everything, there are several courses of action:
1. Remove features.
2. Pick Smaller components
3. implment the same features using less components.
4. daughterboards, requiring carefully cutting nets between sections of the PCB such that it can be re-implemented using pin headers.
	- Note, the use of hirachical sheets should make this process far easier, with the caviat that the use of Global labels may have made this more difficult.
	TODO:
	- Step 1: replace all global power labels in hirarchical sheets with LOCAL net labels. I dont like the use of net labels for joining wires as I beleive it is less clear when
	reading the schematic, however this avoids the issue of having global labels connect "In the background"
	- Step 2: Break nets going between main and MCU hirachical sheet, and rejoin them using pin headers.



