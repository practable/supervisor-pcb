# [3]  System Specification - [Project Title]

_This form is intended to derive low level hardware & software specification from the ***Validated***  
High Level Requirements Capture Form [[1]requirements_capture.md](https://github.com/PanGalacticTech/project_template/blob/main/%5B1%5Drequirements_capture.md) and
[[2]system_optioneering.md](https://github.com/PanGalacticTech/project_template/blob/main/%5B2%5Dsystem_optioneering.md) <br>
Its scope can be adapted to suit projects of varying complexity_ <br>

****************************************************************************************************************************
## [2.2] System Specification Description

_System Specifications for Hardware & Software are derived from and traceable back to the High level Requirements. At this stage optioneering should be
complete, and the design direction finalised._

<!-- NOTE: Origionally I had this document specified as "Low Level Requirements" given past training I had on embedded systems development in aviation, however I 
think this approach was far in excess of what is required for this kind of project, so I have merged "low level requirements" and "system specification" into a single step -->


## [2.3]Example System Specification - [ISOpower]

### [2.3.1]Hardware Specification
_Hardware specification should outline specific hardware devices, circuit design and hardware archetectures chosen to meet high level requirements._

<!-- NOTE: Spreadsheet would be better for comparason of features of components but I see value in documenting major components here too? -->

_Hardware Specification may contain the following subsections:_
- Hardware Architecture
- Major Components - Can be specific or requirements set out for comparason of specific components
- Circuit Design
- Other

### Hardware Architecture & Description

**[HL.1, HL.2, HL.3]**
> The hardware will comprise of a single PCB to home the 2 DC/DC converter modules. 
> These require local fan cooling for which +12v power and mounting holes will be provided.

**[HL.7]**
> 24v Power input will be via XT60 Connector mounted directly on PCB. 

**[HL.5]**
> MCU will be AtMega328p integrated to PCB with ESP32-WROOM-32UE as a WiFi tranciever. MCU will take ADC readings from 2 [Allegro ACS712](https://www.sparkfun.com/datasheets/BreakoutBoards/0712.pdf) current sensing modules,
> one between the DC/DC module and the 12v bus, the other between the 2nd DC/DC module and the 5v bus. Each MCU 

**[HL.5, HL.6]** 
> A voltage divider will be used with an additional ADC input to monitor the voltage of the 12v bus. <br>
> - R1: 100k <br>
> - R2: 56k <br>
> This will allow measurements from 0v to ~14v to be measured by the microcontroller ADC, while limiting current draw to a few microamps.
> Input to the MCU will be protected by a 5.1v Zener diode, incase of voltage spikes greater than can be mitigated by the voltage divider.

**[HL.9, HL.4, HL.13]**
> The 5v Bus will be distributed to 5 USB outputs via individual high side MOSFET switches for each channel,
> these will be connected source to 5v bus, drain to USB output, and gate to the logic circuit used to 
> trigger a power shutoff condition.
> 
> Solder bridges will be provided on the PCB to bypass these MOSFETs, in the case they are not required.


**[HL.4, HL.13]**
> Logic circuit to control power to each 5v USB output will follow the following logic, if: <br>
> A = microcontroller digital pin (1 per channel, logic level HIGH = channel deactivated) <br>
> B = Voltage Monitoring circuit (1 per +5v Bus, logic level HIGH = off nominal voltage detected)  <br>
> C = Output to MOSFET gate (1 per channel, logic level HIGH = MOSFET OFF state) <br>

> IF A OR B == HIGH: C = HIGH.



**[HL.13]**
> The voltage protection circuit will comprise of 2 TL431 Voltage reference ICs set as a window comparator. This circuit will
> output logic level LOW in the case +5V_BUS is pulled off nominal. (4.6v - 5.5v).
> 

**[HL.7, HL.8]**
> 12v bus power will be distributed to 5 XT30 connectors, mounted directly on the PCB. 

 **[HL.10]**
> Reverse voltage protection will be acheived via a P channel MOSFET[^RevVolt] at +Vcc in.

**[HL.11]**
> The system will be protected from overcurrent conditions by a 20A fuse between Vcc in+ and 24v bus. 

**[HL.12]**
> PCB dimensions will be 100x120mm. 

**[HL.14]**
> LM3916 Dot graph drive IC will be used on each voltage bus, 5v, 12v and 24v. Some experimentation may be required to select the correct
> circuit layout & resistor selection for each application. 24v bus will require additional voltage divider,<br>
> R1: 100k <br>
> R2: 56k <br>
> to scale voltage to correct input for LED driver. 24Vin =~ 8.6Vout


_Optional:_
> The PCB will contain footprints to allow 12v outputs to be switched via additional MOSFETs, as well as solder bridges to enable the PCB to be used without. [Dependent on overall size & space left after all other requirements have been met]

-----------------------------------------------------------------------------------------------------
### Major Components

#### DC/DC Converters
##### Option 1: <br>
**Non-Isolated DC-DC Converter, 3.3 → 15V dc Output, 20A**
| Attribute          	|  Value 	                            |  Notes
|---	                |---	                                |---
| **Part Number:**   	| I6A4W020A033V-001-R               	| 
| **Supplier:**     	| RS Components                      	|   
| **Vin:**          	| 9 - 40v                            	|   	
| **Vout:**           |  3.3 - 24v                          |   
|**Power:**            |    250W                            |     
| **Price:**           |  £44.66                            |   
| **URL:**              | https://uk.rs-online.com/web/p/non-isolated-dc-dc-converters/1813289    |     
| **Notes:**           | -     |    
|**Requirements Met:**  |  (HL.1, HL.2, HL.3)        |




#### P-Channel MOSFET for Channel Switching
_Use: High side power switch_
1. Switching of 5v USB power from bus to individual outputs
2. Switching of 12v power from bus to individual outputs (optional feature)
3. MOSFET is ON when gate is @ 0v, OFF when gate is driven to VDD

_Component Requirements:_
| Attribute | Value        | Notes |
|---        |---           |---    |
| Vds        | > (-)21V      | Drain/Source Breakdown Voltage = Operating Voltage + 70% |
|Id         | > (-)6A        | Max Continuous Drain Current > Stall Current of Motor |
| Vgs       | ~ -4.5       | Gate - Source Threshold Voltage[^Vgs] |
| Rds(on)   | <2 ohm       | Static Drain-to-Source-ON-Resistance[^Rds] @ Vgs |

_In the case the requirements for a component are known, however the specific part is unknown, it would be best to use a [spreadsheet](https://github.com/PanGalacticTech/project_template/blob/main/%5B2A%5Dcomponent_compare.xlsx) to weigh up alternative options._

##### Option 1: <br>
**IRF5305PBF P Channel MOSFET**
|Attribute        | Value                                            |Suitable  | Notes |
|---              |---                                               |---       |---    |
|Part Number:     |  IRF5305PBF                                      |          |       |
|Supplier:        | Farnell                                          | [x]      |       |                 
|Vds              |  -55V                                            | [x]      |       |     
|Id               |  -31A                                            | [x]      |       |  
|Rds(on) @ -10v   |  0.06                                            | [x]      |       |      
|Price:           |  £2.088                                          | [x]      |       |      
|                 |                                                  |          |       |
|URL:             |  [IRF5305PBF - Farnell](https://uk.farnell.com/infineon/irf5305pbf/mosfet-p-55v-31a-to-220/dp/8648255) |         |        |
|Availability     |   In Stock                                       | [x]       |       |
|Notes:           |  |         |       |                                                                            
|Meets Requirements: |                                               | [x]     |       |
    

#### P-Channel MOSFET for Reverse Volatage Protection
_Use: Reverse voltage protection_
1. MOSFET is ON when gate is @ 0v, OFF when gate is driven to VDD

_Component Requirements:_
| Attribute | Value        | Notes |
|---        |---           |---    |
| Vds        | > (-)21V      | Drain/Source Breakdown Voltage = Operating Voltage + 70% |
|Id         | > (-)6A        | Max Continuous Drain Current > Stall Current of Motor |
| Vgs       | ~ -4.5       | Gate - Source Threshold Voltage[^Vgs] |
| Rds(on)   | <2 ohm       | Static Drain-to-Source-ON-Resistance[^Rds] @ Vgs |

_In the case the requirements for a component are known, however the specific part is unknown, it would be best to use a [spreadsheet](https://github.com/PanGalacticTech/project_template/blob/main/%5B2A%5Dcomponent_compare.xlsx) to weigh up alternative options._

##### Option 1: <br>
**IRF5305PBF P Channel MOSFET**
|Attribute        | Value                                            |Suitable  | Notes |
|---              |---                                               |---       |---    |
|Part Number:     |  IRF5305PBF                                      |          |       |
|Supplier:        | Farnell                                          | [x]      |       |                 
|Vds              |  -55V                                            | [x]      |       |     
|Id               |  -31A                                            | [x]      |       |  
|Rds(on) @ -10v   |  0.06                                            | [x]      |       |      
|Price:           |  £2.088                                          | [x]      |       |      
|                 |                                                  |          |       |
|URL:             |  [IRF5305PBF - Farnell](https://uk.farnell.com/infineon/irf5305pbf/mosfet-p-55v-31a-to-220/dp/8648255) |         |        |
|Availability     |   In Stock                                       | [x]       |       |
|Notes:           |   DO NOT USE FOR REVERSE POWER PROTECTION ON 24V BUS. Vgs Max is 20v|         |       |                                                                            
|Meets Requirements: |                                               | [x]     |       |

#### AtMega328P MCU

#### Allego ACS712

#### 
-----------------------------------------------------------------------------------------------------

### Circuit Design & Schematic
_Final Circuit Design, Schematics & Justifications for design_




_____________________________________________________________________________________________________
 
#### [2.3.2]Software Specification

_Specify the software requirements, functions, frameworks and tools required to meet the high level requirements_

#### Tools:
| Tool | Purpose | Justification |
|---   |---      |---            |
|Arduino IDE| Software Development | Speed & ease of development for Arduino IoT functions |
|C++ | Programming Language | Native to Arduino environment |
|InfluxDB | Remote storage of power consumption data | Ease of setup & ease of posting data from remote devices |
|Grafana  | Graphic display of power consumption via web interface | off the shelf solution that can integrate control methods for sending HTTP requests back to controller |

### Software Specification

- ADC Samples of current sensor will be taken every 250mS  <!-- Let me know if these timings are suitable  -->
- ADC samples of 12v bus voltage will be taken every 250mS <!-- Let me know if these timings are suitable  -->
- Power Channel MOSFETS are "Active Low" Therefore channels will be turned off driven by a HIGH pulse from microcontroller.
- Seperate API for each power channel "on", "off" and "restart",



When to review? 
*System Specification should undertake a review process, to ensure the design meets the clients needs before moving to ***Fabrication*** <br>*


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
      
[1v1]: [Arduino: Analog Reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/)

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
