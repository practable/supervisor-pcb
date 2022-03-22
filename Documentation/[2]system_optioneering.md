# [2]  System Optioneering - [Project Title]

_This form is intended to assist in optioneering to derive low level hardware & software specification from the ***Validated***  
High Level Requirements Capture Form [[1]requirements_capture.md](https://github.com/PanGalacticTech/project_template/blob/main/%5B1%5Drequirements_capture.md).
Its scope can be adapted to suit projects of varying complexity_ <br> 
*******************************************************************************************************************************************************

## [2.1] Design Tradeoffs & Optioneering
_Space to work through different options before deciding on specific low level requirements & system specification for hardware & software
It is useful to highlight situations where one design decision is dependent on other decisions, or where a design decision will have known, or forseeable impacts on
other decisions later._

### Preamble
_Introduction to the design approach if required_ <br>

### Optioneering Diagrams
_Flowcharts can be used to explore the relationships between different options, and display graphically how making specific design decisions
will affect the other available options._

![hardware optioneering diagram](https://user-images.githubusercontent.com/53580358/149789762-3f4a02a2-bd1c-419f-8d7e-c849cabb182d.png)
_Flowchart showing the different communications standards and methods that could be used to connect the user interface and the microcontroller, dependent on
low level hardware choices_


### Optioneering Table
_This is an example of the options that may wish to be explored for this project, however there may be alternative ways of displaying this information
that are more suitable_

|Requirement| Function                      | Options                       | Sub-Options                                | Hirarchy  | Notes  |
|---        | ---------------------------   | ---------------------------   | -----------------------------------------  | -------   |----    |
|HL:(4,5,6) | Controller for Current Sensing| Integrated MCU on PCB         | CH340 Driver for USB comms to Raspi        |    3      |        |
|"          |           "                   |           "                   | ublox Wifi module & remote database server |    2      |        |
|"          |           "                   |           "                   | ESP32 performs as MCU controller And/Or Wifi Module|    1   |  requires 3.3v logic if used as MCU|
|"          |           "                   | Arduino Nano 33 IoT| Local Raspberry Pi |    4    | will require 8 port switch to accomidate extra RasPi in ISO Container | 
|"          |           "                   |    "             | Remote Raspberry Pi  |    3    | Will Require external WiFi Antenna to ensure robust Connection|
|           |                               |                               |                                            |           |        |
|HL:(4)     | Power Switching               |N-Channel Low Side MOSFET      |                                            |    3      |        |  
|"          |           "                   |P-Channel High Side MOSFET     |                                            |    1      | Difficult to source suitable MOSFET|  
|"          |           "                   |Relay                          | Normally Closed                            |    2      | Expense       |    
|"          |           "                   |           "                   | Latching                                   |    4      | Expense, Reliability       |      
|           |                               |                               |                                            |           |        |  
|HL:(1,2,3) | Power Supply DC/DC Conversion | COTS Modules                  |                                            |     1     |        |    
|"          |           "                   | ReEngineer & Integrate w/ PCB |                                            |     4     |        |  
|"          |                               |                               |                                            |           |        |
|HL:(7)     | Power Input Connector         | Screw Terminals               |       |  4  |                                             |
|"          |         "                     | XT60 - 60A  Connector         |       |  1  | Quick Disconnect Compared to screw terminals, easy to solder, easier PCB mounting|
|           |                               |                               |                                            |           |        |  
|HL:(7)     | 12v Power Output Connectors   | 2.1mm Barrel Jacks            |       |  4  | Hard to find with range of options, easy to damage|
|"          |           "                   | XT30 - 30A Connector          |       |  1  | Easy to source, many differnt options, well defined specifications|
|           |                               |                               |                                            |           |        |  
|HL:(5)     | Voltage Sensing               | Voltage Divider on 12 bus   | | 1 | Can't be used for 5v bus as MCU would share Vcc ref. Must protect MCU from voltage spikes|
|"          |     "                         | Voltage sense IC            | | 2 | Cant find suitable option, open for reccomendations, could be used for both 12v and 5v bus|
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Circuit Design & Hardware Optioneering [Hardware]
_Exploration of circuit elements & Hardware that might be used to meet design objectives_


#### Overvoltage Protection of 5v USB Bus ***[HL.13]***
_The aim of overvoltage protection for the 5v bus, is to protect the raspberry pis in the event +12v power is accidently applied to this bus, pulling all the outputs to 12v
and causing damage. Several possible approaches will be discussed below_

##### Approach 1 - Zener Diode

>    5.1v zener diode reverse biased between the USB outputs 5v rail, and GND.
>    A 100ohm resistor must be between the potential source of over voltage and the zener diode.[^zener]

***Problems with this approach***

>    If the source of the overvoltage is also on the USB bus, this does not nessissarily solve the problem,
>    as the current will flow unimpeded through the zener diode, causing overheating and component failure. 
>    If it fails open circuit (likely) then the protection is no longer active and the 5v bus will be pulled to 12v.

> As the likely source of the overvoltage would be the other USB inputs, each V+ rail would need a 100ohm resistor, with a zener diode on the supply side of the resistor.

##### Approach 2 - Using the MOSFET That is Already There

>    As the USB channel is already designed to be switched off via a logic high signal (+5v) from a microcontroller, 
>    could that same MOSTFET also be triggered with logic high if a fault condition is detected?
>    This solution would have to be passive, i.e not be reliant on the MCU to trigger, as this
>    would delay response and would not stop damage from occuring.
>     <br>
>     A logical OR gate could be used to provide a buffer between the logic HIGH/LOW pin on the microcontroller, and the
>     other system for providing a logical HIGH in the case the 5v bus moves out of tolerance. 1 logical OR gate would be required for each USB output,
>     The output of each logic gate, feeds the gate of each MOSFET

***OverVoltage Detection***

> Voltage Supivisor/detection ICs: <br>
> [TL431 Voltage Reference, Adjustable Shunt](https://uk.farnell.com/on-semiconductor/tl431acdg/voltage-ref-shunt-2-495v-36v-soic/dp/1651199)<br>
>  Voltage is monitored on 5v rail, and IC outputs a logic high if voltage goes outside of set nominal band. <br>
>  
> **Use Case**
> [TI TL431 for Under & Overvoltage Detection]( https://www.ti.com/lit/an/slva987a/slva987a.pdf?ts=1642107195143&ref_url=https%253A%252F%252Fwww.google.com%252F)[^uvov]
> In this case, the V(high) and V(low) thresholds are set via 4 resistors. Calculations outlined below[^tl431] 

> TL431 has a minimum cathode current of 1mA, so resistor selection must be checked to meet this requirement.

> Resistor Values Estimated:
> R1: 470r      <br>
> R2: 560r     <br>
> Vhigh ~ 5.47v   <br>
> <br>
> R3: 560r   <br>
> R4: 470r   <br>
> Vlow ~ 4.8v
>
> R5 = 220r <br>
> <br>
> Using these values & <br> I = (Vcc - Vref)/R3 (High edge) & I = (Vcc - Vref)/R5 (Low edge) [No sure if correct best guess given forum posts & datasheet] <br>ere
> Ika ~ 4mA for high edge & 11mA for low edge



***Implementing This Solution***
> Requires: <br>
> 5 * OR Gates <br>
> > <br>
> To make these gates from common gates, it would require: <br>
> 15 * NAND Gates. (3 req for OR gate) <br>
> OR <br>
> 10 * NOR Gates. (2 req for OR gate) <br>
> Suggest: <br> 
> 3 * [MC74HC02ADG SMD Quad Input NOR Gate](https://uk.farnell.com/on-semiconductor/mc74hc02adg/ic-74hc-cmos-smd-74hc02-soic14/dp/9666893)


---

#### Power Bus Visual Fault Indications ***[HL.14]***
_The aim of this requirement is to provide additional information to engineers testing, maintaining and debugging the system. For this
reason it should be independent of all other systems, and simplified as much as possible._

>   I much prefer the idea of independent indication for each bus, rather than a traffic light with 
>   "All Nominal" "Something Off Nominal" "Everything Off Nominal" indication, as I believe this is; <br>
>   1: less useful than say "A Okay" "B Okay" "C Okay" indications and <br>
>   2: it may also be harder to design if we take a passive approach, i.e: This system should work independently
>   of any microcontrollers.

##### Option 1

>   A window comparator circuit[^comp] could be used to display whether each bus is falling within a predefined "nominal" window,
>   however this circuit would be reliant on stable Vcc, so is not useful for detecting if Vcc is off nominal.
>   An independent linear or LDO regulator could provide independent reference voltages to solve this problem, but 
>   increase in cost & complexity.



##### Option 2

> Led VU Meter, Options detailed [^vu]  [LM3916 Dot/Bar Display Driver](https://cdn.sparkfun.com/datasheets/Components/General%20IC/lm3916.pdf) Monitors 
> analog voltage level and lights up to 10 LEDs sequentially
> Supply Voltage from 3v to 25v - Suggest it runs from 12v rail for each use case. Input can handle from 0 to 35v 


***Assessment***
This option did not work well, as the window for the "okay" LED was far too wide, I managed to get it to indicate high voltage at 5.5v, however getting it to register
low voltage at anything >4v seemed to fail. It also did not perform well with off nominal supply voltage.

#### Option 3
> Use the features of the DC/DC supplies[^dcdc]

> DC/DC supply can indicate an off nominal voltage rail by pulling a logic HIGH to ground. This can be monitored by the MCU and set error LEDs. This will also enable easy 
> reporting & monitoring of power status.
> Can be used for visual indication lEDs & report via JSON.


---

#### MCU Selection

The best options for MCU seem to be either;
[AtMega328p](https://uk.farnell.com/microchip/atmega328p-an/mcu-8bit-atmega-20mhz-tqfp-32/dp/2443178?st=ATmega328P) combined with CH340 for USB comms & programming, ISP header for programming bootloaders, and an WiFi transcever as a peripheral device, or <br>

[ESP32-WROOM-32U](https://www.mouser.co.uk/ProductDetail/Espressif-Systems/ESP32-WROOM-32UM113DH3200UH3Q0?qs=W%2FMpXkg%252BdQ4Fqx%2FReRQpFQ==&mgh=1&vip=1&gclid=CjwKCAiAxJSPBhAoEiwAeO_fPwE6kImUAnBTI5SyodKJNS7nNKTfdQ13Md3OplGP5AphD8abym4PYBoCbGkQAvD_BwE), with the same USB interface and ISP header, but without the need for an additional WiFi transcever. This has a number of advantages and disadvantages. 

The major disadvantage is the ESP's requirement for 3.3v logic, this will likely require additional drivers for actuation of the MOSFET switches,
as well as voltage dividers and additional scaling on ADC inputs from the [ACS712 Hall Effect Linear Current Sensor](https://www.sparkfun.com/datasheets/BreakoutBoards/0712.pdf)
For this reason, using the AtMega328p as the main MCU seems like it will cause less issues with the rest of the circuit design.

However the selection of the peripheral WiFi adaptor throws up an ironic aside, it seems much cheaper to use ESP32
as a WiFi device than sourcing dedicated WiFi transceiver modules like the ublox nina.
The ESP32 is available with the option to connect an external antenna, which makes the system more adaptable for use
in areas that may not have adiquate WiFi signal with the antenna obscured inside a metal box.

***Conclusion***

The board will use both AtMega328p to act as the hardware controller, and ESP32 to act as wifi & higher level control. This will also act as a proving ground for using 
mixed controller boards, interfacing ESP32 with other MCUs, and potentually offering up the ability to expand the scope of the power supply module later with more advanced 
software run on the ESP32, with the AtMega handling the lower level hardware monitoring.

[Info on using ESP32 as WiFi adaptor for AtMega328p](https://icircuit.net/arduino-interfacing-arduino-uno-esp32/2134)[^esp32]



****************************************************************************************************************************

### Software Design & Optioneering [Software]
_Exploration of software, firmware and development tools that might be used to meet design objectives and test system performance_


### Software Structure Optioneering

#### Option A

- Arduino running state machine framework
- websocket server responds to HTTP GET requests for control of power channels
- concurrently taking analogRead() of 2 ADC inputs, and sending to external database with HTTP POST requests over wifi
- Data is pulled from database using graphing tool, like Grafana, which is built around a web accessable user interface.

#### Option B

- Arduino running state machine framework
- websocket server responds to HTTP GET requests 
- concurrently taking analogRead() of 2 ADC inputs, and sending to Raspberry Pi over USB communication.
- Raspberry pi requires script to place data received over COM port into web accessable format. 


#### Option C

- Arduino running state machine framework
- [Interfacing using JSON formatted data](https://github.com/dpreid/pidui/issues/5)
- concurrently taking analogRead() of 2 ADC inputs, and sending to client as JSON formatted data.
- Ties into existing infrastructre




_______________________________________________________________________________________________________________________________________________________

### [2.4] Requirement Matrix

_Info On Requirements Matrix & Link to: [Requirements Matrix Document](https://broken_link.com)_

_______________________________________________________________________________________________________________________________________________________
#### References

- [Rugged Circuits: 10 Ways to Destroy an Arduino](https://www.rugged-circuits.com/10-ways-to-destroy-an-arduino)
- [High Side vs Low Side Switch](https://www.baldengineer.com/low-side-vs-high-side-transistor-switch.html)
- [Important Stuff: MOSFET Specs You Need to Know](https://www.embeddedrelated.com/showarticle/809.php)
- [Using the Atmel ATmega328P Analog to Digital Conversion Module](https://ece-classes.usc.edu/ee459/library/documents/ADC.pdf)

*******************************************************************************************************************************************************

#### Notes

**VGS & Rds Explanation**

_Assuming That_

|Attribute | Value | Max Current Flow
|---|---|---|
| Source Voltage | 5v |
|Rds(on) @ Vgs -4.5v | 0.0133 ohm      | 5/0.0133 = 376A |
|Rds(on) @ Vgs -10v   | 0.0083 ohm      | 5/0.0093 = 537A  |


#### Footnotes

[^Rds]: Drain-to-Source On-Resistance <br>
        - If current required is 2.5A, then R=5/2.5: R=2ohm absolute max Rds during operation (in practice must be much lower)   <br>
        - If Vcc = 5v, and gate is pulled to 0v GND, then Vgs ~-5v                                                                <br>
        - Datasheet shows Rds(on) @ Vgs -4.5 will be ~ 0.0133 ohm                                                                     <br>
        - If Vcc = 12v & Gate is pulled to 0v GND, then Vgs ~ -10v therefore Rds(on) ~ 0.0093 ohm                                                       <br>
        - HOWEVER, controller can only provide 5v so will need drivers to fully turn off MOSFET, see[^Vgs(th)]                              <br>

[^Vgs(th)]: Gate-Source Threshold Voltage <br>
            - Datasheet shows that Vgs must be >-2.0V to turn off device  <br>
            - i.e. Id = -250 uA @ Vds (Maximum Drain - Source voltage differential) <br>
            - Therefore if VCC is 12v, Gate Voltage must be driven to >10v to turn off MOSFET <br>

[^V&V]: Verification & Validation - What is it? <br>
        - Verification - _"Does the implementation meet the requirements?"_ <br>
        - Validation   - _"Are the requirements correct"_
        
<!--[^2]: Ruggeduino >5v cutoff circuit -->
      <!-- - ![image](https://user-images.githubusercontent.com/53580358/148758688-282c6b19-230f-4211-98ce-a5ba380fc2d2.png) -->
          
<!-- [^3]: Estimated current consumption of cutoff circuit
      - R = 17kohm, V = 5v. 
      - I=V/R
      - I = (17k / 5) = [2.9\*10^-4] A -->
      
[^1v1]: [Arduino: Analog Reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/)

[^RevVolt]: [Infineon Reverse Voltage Protection Methods](https://www.infineon.com/dgdl/Reverse-Batery-Protection-Rev2.pdf?fileId=db3a304412b407950112b41887722615) <br>
             ![image](https://user-images.githubusercontent.com/53580358/149346402-d48d8c97-2ba4-4139-989e-2c378938aefb.png)

   
[^zener]: [Designing overvoltage protection using zener diodes](https://components101.com/articles/designing-an-overvoltage-protection-circuit-using-zener-diodes)

[^comp]: [op-amp comparator](https://www.electronics-tutorials.ws/opamp/op-amp-comparator.html)

[^vu]: [Single Transistor LED VU meter](https://electronicsarea.com/6-led-vu-meter-using-one-transistor/) <br>
       

[^uvov]: [LM431 Datasheet](https://www.ti.com/lit/ds/symlink/lm431.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1642092638827&ref_url=https%253A%252F%252Fwww.ti.com%252Fgeneral%252Fdocs%252Fsuppproductinfo.tsp%253FdistId%253D10%2526gotoUrl%253Dhttps%253A%252F%252Fwww.ti.com%252Flit%252Fgpn%252Flm431) <br> ![image](https://user-images.githubusercontent.com/53580358/149549094-5a31fedb-78fb-4ca3-9df5-5213b09f50f0.png) <br>
<!-- ![image](https://user-images.githubusercontent.com/53580358/149550148-76459666-dd3e-4661-bf27-dfcf147a4180.png) <br> -->



[^tl431]: Voltage Window Calculations: <br>
          - Vh=(1+(R2/R)1)*Vref   <br>
          - Vl=(1+(R4/R3))*Vref

[^dcdc]: [i6a4w_spec](https://product.tdk.com/en/system/files?file=dam/doc/product/power/switching-power/dc-dc-converter/specification/i6a4w_spec.pdf)

[^esp32]: <br> ![image](https://user-images.githubusercontent.com/53580358/150812828-c129d159-ef26-4909-93cf-39b9f3dced7a.png)

