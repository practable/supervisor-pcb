# Using Remote Labs Supervisor PCB README

_This document is intended to be a useage guide for the Remote Labs Supervisor PCB, and document the different use cases and configurations it is capable of._

For coded examples of the various features please see [PCB Unit Tests](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/tree/main/Verification%20Tests/PCB%20Unit%20Tests), which contains
arduino code firmware used during testing all hardware features of the PCB.

For the purposes of this document, it is assumed that the Motherboard PCB is populated with both Arduino Nano IoT 33 Daughterboards __(A1 & A2)__, with shift registers installed, and NOT the bare bones SAMD21 MCU.
A seperate document will be provided for cases in which SAMD21 MCUs are mounted to the motherboard directly.


### Pin Naming and Shift Registers

_All MCU pins will be referenced by the Arduino Pin Numbers in this document. 
Additional pins are sourced via Shift Registers attached to each MCU.
Shift Register pins are labelled as Q0 - Q7.
Both MCU connections to their independent shift registers are detailed below._

MCU Pin |  Shift Register Function 	|
---		| ---						|
D8		| LATCH	(Write to Register)	|
D11		| MOSI (Data)				|
D13		| SCK						|

#### Pinout Diagrams

_MCU and Shift Register Pinout diagrams_

##### Supervisor MCU

##### Student MCU


### Powering the System

The System should be provided 12v DC power via the yellow XT60 connector __J3__. The system is specified to draw a maximum of ~ 8A depending on experiment configuration, ensure that power supply selected is sufficient for specific use case.

Diode D6 (Blue) will light to show correct polarity power is provided to input.
Diode D7 (Orange) will light to show 3V3 DC power is available to microcontrollers and periferal devices.

Motherboard has reverse polarity protection, however care should be taken to ensure correct orientation of power input. - NOTE: Currently missing protection diode- awaiting delivery


### Programming the MCUs

Each MCU, supervisor and student are able to be programmed via the USB connector on the daughterboard, or via UART using the 5 pin headers __J26 Student_Prog_Header__, and __J1 Super_Prog_header__.

For UART Programming, a hat is provided for raspi GPIO pins. 5 pin cable should be connected from Raspi hat to UART Programming connector on motherboard.

__The USB connectors mounted to the __Motherboard__ should not be used if Arduino Development boards are installed, and are UNTESTED for use with bare bones MCUs installed__

-----

## Use Case 1 [Spinner Experiment]

_In this configuration the following modules should be mounted to the motherboard:_

- Infineon DC Motor Control Shield - A3

_In this configuration the following external hardware should be connected as follows:_

- DC Motor, wired to the OUTER two pins on __J18 DC Motor Output__
- Optical Encoder, plugged into __J25 Optical Encoder__


### Using the DC Motor

DC Motor PWM is routed to Infineon DC Motor Controller module via the following logic:

![image](https://user-images.githubusercontent.com/97303986/179261400-5589a8e7-a57c-4d85-9150-5109dd07229f.png)

If MOTOR_DIR_A is driven HIGH, PWM is routed from STUDENT_MOTOR_PWM or SUPERVISOR_MOTOR_PWM to MOTOR_OUT_1
If MOTOR_DIR_B is driven HIGH, PWM is routed from STUDENT_MOTOR_PWM or SUPERVISOR_MOTOR_PWM to MOTOR_OUT_2

Care must be taken to avoid driving MOTOR_DIR_A and MOTOR_DIR_B to HIGH at the same time as this will cause shoot through.

In Order to avoid shoot through condition, Student does not have direct input to MOTOR_DIR_A or MOTOR_DIR_B. These outputs are spoofed via the Supervisor MCU.



The MCU able to pass PWM signal to Motor Control Module is selected by MCU_MOTOR_SELECT pin. When HIGH - STUDENT_MOTOR_PWM is active, when LOW - SUPERVISOR_MOTOR_PWM is active.

In order to enable the DC Motor Control Module, OUT_M_ENABLE must also be set HIGH. This is routed from either MCU using the same logic as above, when MCU_MOTOR_SELECT is HIGH, ENABLE is routed from STUDENT_MOTOR_EN, when it is set LOW, ENABLE is routed from SUPERVISOR_MOTOR_EN.

M_I_SENSE_1 and M_I_SENSE_2 output is buffered and distributed to both MCUs.



### Supervisor MCU

Supervisor MCU uses the following table for DC Motor Control:

MCU 		|Pin 	| Pin Name 		| State 		| Motor Behaviour 		| Notes
---			|---	|---			|---			|---					|---
SUPERVISOR 	|D12 	|MOTOR_DIR_1	| HIGH or LOW	| Sets motor Direction	| IF(D7 == HIGH){D12 MUST = LOW)
SUPERVISOR	|D7		|MOTOR_DIR_2	| LOW or HIGH 	| Sets motor Direction 	| IF(D12 == HIGH){D7 MUST = LOW)
SUPERVISOR	|Q0		|DC_MOTOR_EN	| HIGH			| Enables DC Motor Drive|
SUPERVISOR	|Q1		|STUDENT_M_EN	| LOW			| Blocks Student Control, Enables Supervisor Control| 
SUPERVISOR	|A7		|DC_MOTOR_IS1	| ANALOG INPUT	| Current Draw and Fault Condition Detection| 
SUPERVISOR	|A6		|DC_MOTOR_IS2	| ANALOG INPUT	| Current Draw and Fault Condition Detection| 

### Student MCU

Student MCU uses the following table for DC Motor Control: *Note - Student control relys on specific pin configurations of Supervisor MCU*

MCU 		|Pin 	| Pin Name 		| State 		| Motor Behaviour 		| Notes
---			|---	|---			|---			|---					|---
STUDENT 	|D12 	|MOTOR_DIR_1	| HIGH or LOW	| Detected by Supervisor PIN A1	| IF(D7 == HIGH){D12 MUST = LOW)
STUDENT		|D7		|MOTOR_DIR_2	| LOW or HIGH 	| Detected by Supervisor PIN A0	| IF(D12 == HIGH){D7 MUST = LOW)
STUDENT		|Q0		|DC_MOTOR_EN	| HIGH			| Enables DC Motor Drive|
SUPERVISOR	|Q1		|STUDENT_M_EN	| HIGH			| Blocks Supervisor Control, Enables Student Control| 
SUPERVISOR	|A1		|STDNT_DC_M_DIR_1| DIGITAL INPUT| Detects state of Student Direction Pin and Spoofs output if logic != illegal
SUPERVISOR	|A0		|STDNT_DC_M_DIR_2| DIGITAL INPUT| Detects state of Student Direction Pin and Spoofs output if logic != illegal
SUPERVISOR 	|D12 	|MOTOR_DIR_1	| HIGH or LOW	| Sets motor Direction - Spoofed from A1	| 
SUPERVISOR	|D7		|MOTOR_DIR_2	| LOW or HIGH 	| Sets motor Direction - Spoofed from A0	| 
STUDENT		|A7		|DC_MOTOR_IS1	| ANALOG INPUT	| Current Draw and Fault Condition Detection| 
STUDENT		|A6		|DC_MOTOR_IS2	| ANALOG INPUT	| Current Draw and Fault Condition Detection| 

### Using the Optical Encoder

_Optical encoder signals are buffered and provided to both MCUs simaltaniously, therefore getting useful data from Optical Encoder is the same process for both MCUs_

MCUs use the following table for Optical Encoder detection:

MCU 		|Pin 	| Pin Name 		| State 								| Notes
---			|---	|---			|---									|---
Both	 	|D2 	|ENCODER_B		| EXTERNAL INTERRUPT / DIGITAL INPUT	| For best performance, External Interrupt used for edge detection of Encoder waveform
Both		|D3		|ENCODER_A		| EXTERNAL INTERRUPT / DIGITAL INPUT 	| Alternative pin for External Interrupt.
Both		|D4		|ENCODER_INDEX	| DIGITAL INPUT							| Used to track center detent of optical encoder (Untested in software)


-----

## Use Case 2 [Governer Experiment]

In this configuration the following modules should be mounted to the motherboard:

- Infineon DC Motor Control Shield 	- A3
- DRV8825 Stepper Motor Driver		- A4

___DC Motor & Optical Encoder are accessed as Use Case 1 above___


In this configuration the following external hardware should be connected as follows:

- DC Motor, wired to the OUTER two pins on __J18 DC Motor Output__
- Stepper Motor, plugged into __J19 Stepper Motor Output__
- Optical Encoder, plugged into __J25 Optical Encoder__
- Limit Switch, plugged into __J23 limit_switch_A__


### Using the Stepper Motor

Stepper Motor Driver inputs are routed via the following logic:

![image](https://user-images.githubusercontent.com/97303986/179261535-dfac3f53-abda-467a-adae-726d47ff7c55.png)

When MCU_STEP_SELECT is HIGH, inputs are routed from STUDENT MCU. When MCU_STEP_SELECT is LOW, inputs are routed from SUPERVISOR MCU.

STEPP_EN is driven from Supervisor MCU Only, however does not seem to have any effect on stepper motor function. - Requires further investigation.

STEPPR_FAULT output is buffered and distributed to both MCUs.

LIMIT_1 Limit switch input is buffered and distributed to both MCUs.

### Supervisor MCU

Supervisor MCU uses the following table for Stepper Motor Control:

MCU 		|Pin 	| Pin Name 		| State 		| Motor Behaviour 									| Notes
---			|---	|---			|---			|---												|---
SUPERVISOR 	|D6 	|STEPP_STEP		| PULSE			| Motor advances 1 step per pulse					| 
SUPERVISOR	|Q2		|STUDENT_STEP_EN| LOW			| Blocks Student Control, Enables Supervisor Control| 
SUPERVISOR	|Q4		|STEPP_DIR		| HIGH or LOW	| Sets Stepper Motor Direction						|
SUPERVISOR	|Q5		|STEPP_SLP		| HIGH or LOW	| Enables and Sleeps motor to avoid overheating 	| MUST BE HIGH? to enable					| 
SUPERVISOR	|Q6		|STEPP_RST		| HIGH or LOW	| Resets controller board after fault condition 	| MUST BE HIGH? to enable					| 
SUPERVISOR	|Q7		|STEPP_EN		| HIGH or LOW	| Enables motor driver board						| NO DECERNABLE EFFECT? - Needs Testing		| 
SUPERVISOR	|A5		|STEPP_FLT		| DIGITAL INPUT	| Fault reporting from Stepper Control daughterboard| HIGH = NO FAULT, LOW = FAULT 				| 
SUPERVISOR	|A4		|LIMIT_1		| DIGITAL INPUT	| Limit Switch Detection.							| LOW = Switch Pressed 						| 



### Student MCU

Student MCU uses the following table for Stepper Motor Control: *Note - Student control relys on specific pin configurations of Supervisor MCU*

MCU 		|Pin 	| Pin Name 		| State 		| Motor Behaviour 									| Notes
---			|---	|---			|---			|---												|---
STUDENT 	|D6 	|STEPP_STEP		| PULSE			| Motor advances 1 step per pulse					| 
SUPERVISOR	|Q2		|STUDENT_STEP_EN| HIGH			| Enables Student Control, Blocks Supervisor Control| 
STUDENT 	|Q4		|STEPP_DIR		| HIGH or LOW	| Sets Stepper Motor Direction						|
STUDENT		|Q5		|STEPP_SLP		| HIGH or LOW	| Enables and Sleeps motor to avoid overheating 	| MUST BE HIGH? to enable					| 
STUDENT		|Q6		|STEPP_RST		| HIGH or LOW	| Resets controller board after fault condition 	| MUST BE HIGH? to enable					| 
SUPERVISOR	|Q7		|STEPP_EN		| HIGH or LOW	| Enables motor driver board						| NO DECERNABLE EFFECT? - Needs Testing		| 
STUDENT		|A5		|STEPP_FLT		| DIGITAL INPUT	| Fault reporting from Stepper Control daughterboard| HIGH = NO FAULT, LOW = FAULT 				| 
STUDENT		|A4		|LIMIT_1		| DIGITAL INPUT	| Limit Switch Detection.							| LOW = Switch Pressed 						|


#### Additional Stepper Motor Functions

SW1 - Stepper Mode Dipswitches set number of steps per revolution. If UNPOPULATED setting is at MAX RESOLUTION. (1, 1, 1 ) logic for MODE inputs.



## Use Case 3 [Digger Experiment]

In this configuration the following modules should be mounted to the motherboard:

- Infineon DC Motor Control Shield 	- A3

___DC Motor & Optical Encoder are accessed as Use Case 1 above___


In this configuration the following external hardware should be connected as follows:

- DC Motor, wired to the OUTER two pins on __J18 DC Motor Output__
- Optical Encoder, plugged into __J25 Optical Encoder__
- Limit Switch, plugged into __J23 limit_switch_A__
- Servo, plugged into __J20 Servo_A__

In this use case, supervisor must calibrate and track the position of DC motor to avoid equipment collision with self. 

### Supervisor MCU

Supervisor has ultimate control of the Servo PPM output.

Supervisor MCU uses the following table for Servo Motor Control:

MCU 		|Pin 	| Pin Name 		| State 		| Motor Behaviour 									| Notes
---			|---	|---			|---			|---												|---
SUPERVISOR 	|D9 	|SERVO_1		| PPM Output	| PPM Standard sets Servo Position					| 


### Student MCU

Student MCU has no direct output to servo_1, instead supervisor must spoof and constrain output;
given either a PWM signal, or PPM signal from the Student, applied to __Pin A2__ of the supervisorU MCU.

Student MCU uses the following table for Servo Motor Control: *Note - Student control relys on specific pin configurations of Supervisor MCU*

MCU 		|Pin 	| Pin Name 		| State 		| Motor Behaviour 									| Notes
---			|---	|---			|---			|---												|---
STUDENT 	|D9 	|SERVO_1		| PPM or PWM Output	| PPM/PWM used to infer desired position of servo	| 
SUPERVISOR	|A2		|STDNT_SRVO_RX_1| ANALOG INPUT or EXTERNAL INTERRUPT	| Detects infered desired position for servo| 
SUPERVISOR 	|D9 	|SERVO_1		| PPM Output	| PPM Standard sets Servo Position					| 



## Use Case 4 [Pendulum Experiment]

*NOTE: USE CASE UNTESTED*

In this configuration the following modules should be mounted to the motherboard:

- Remote Labs Pendulum PCB Daughterboard - A3

In this configuration the following external hardware should be connected as follows:

- Pendulum Driver, wired to the OUTER two pins on __J18 DC Motor Output__
- Optical Encoder, plugged into __J25 Optical Encoder__

### Supervisor MCU

Supervisor MCU uses the following table for Pendulum Control:

MCU 		|Pin 	| Pin Name 		|Pendulum PCB Pin Name	| State 		| Pendulum Behaviour 	| Notes
---			|---	|---			|---					|---			|---					|---
SUPERVISOR 	|Q0		|DC_MOTOR_EN	| ENABLE	| DIGTAL OUTPUT	| Drive	 |Tried to avoid this being on a shift register - failed can it be moved to another pin? User Thermo A3, and enable
SUPERVISOR 	|D6		|STEPP_STEP		| PENDULUM_PIN_1		| DIGTAL OUTPUT	| Load					|  
SUPERVISOR 	|D12	|DC_MOTOR_DIR_1	| PENDULUM_PIN_7		| DIGTAL OUTPUT	| LED_1 Control			| 	
SUPERVISOR 	|D7		|DC_MOTOR_DIR_2	| PENDULUM_PIN_8		| DIGTAL OUTPUT	| LED_2 Control			| 
SUPERVISOR 	|D9		|SERVO_1		| PENDULUM_PIN_6		| DIGTAL OUTPUT	| LED_3 Control			| 
SUPERVISOR 	|Q1		|STUDENT_M_EN	| PENDULUM_PIN_2		| LOW			| Blocks Student Control, Enables Supervisor Control |
SUPERVISOR	|A7		|DC_MOTOR_IS1	| I_SENSE_1				| ANALOG INPUT	| Current Draw and Fault Condition Detection|  Check which way around these are
SUPERVISOR	|A6		|DC_MOTOR_IS2	| I_SENSE_2				| DIGITAL INPUT	| Current SIGN reporting (+/-)| HIGH = Positive Current, LOW = Negative Current


### Student MCU

Student MCU uses the following table for Stepper Motor Control: *Note - Student control relys on specific pin configurations of Supervisor MCU*

MCU 		|Pin 	| Pin Name 		|Pendulum PCB Pin Name	| State 		| Pendulum Behaviour 	| Notes
---			|---	|---			|---					|---			|---					|---
STUDENT 	|Q0		|DC_MOTOR_EN	| ENABLE	| DIGTAL OUTPUT	| Drive	 |Tried to avoid this being on a shift register - failed can it be moved to another pin? User Thermo A3, and external enable
STUDENT 	|D6		|STEPP_STEP		| PENDULUM_PIN_1		| DIGTAL OUTPUT	| Load					|  
STUDENT  	|A0		|SPARE_0		| PENDULUM_PIN_3		| DIGTAL OUTPUT	| LED_1 Control			| 	
STUDENT  	|A1		|SPARE_1 		| PENDULUM_PIN_4		| DIGTAL OUTPUT	| LED_2 Control			| 
STUDENT  	|A2		|SPARE_2		| PENDULUM_PIN_5		| DIGTAL OUTPUT	| LED_3 Control			| 
SUPERVISOR 	|Q1		|STUDENT_M_EN	| PENDULUM_PIN_2		| HIGH			| Enables Student Control, Blocks Supervisor Control |
STUDENT		|A7		|DC_MOTOR_IS1	| I_SENSE_1				| ANALOG INPUT	| Current Draw and Fault Condition Detection|  Check which way around these are
STUDENT		|A6		|DC_MOTOR_IS2	| I_SENSE_2				| DIGITAL INPUT	| Current SIGN reporting (+/-)| HIGH = Positive Current, LOW = Negative Current




## Additional Features

### WS2812 LEDs

To use WS2812 LED strips with any configuration, the following external hardware should be connected as follows:

- WS2821B LED Strip, connected to __J24 WS2812B LEDs__

__Supervisor MCU__ uses the following table for WS2812B LED Control.


MCU 		|Pin 	| Pin Name 		| State 		| Use			 				| Notes
---			|---	|---			|---			|---							|---
SUPERVISOR 	|D5 	|PIXEL_DATA		| DIGITAL OUTPUT| Sets LED Colour & Brightness	|
SUPERVISOR	|Q3		|STUDENT_PIXEL_EN| LOW			| Blocks Student Control, Enables Supervisor Control		|


__Student MCU__ uses the following table for WS2812B LED Control.: *Note - Student control relys on specific pin configurations of Supervisor MCU*

MCU 		|Pin 	| Pin Name 		| State 		| Use			 				| Notes
---			|---	|---			|---			|---							|---
STUDENT		|D5 	|PIXEL_DATA		| DIGITAL OUTPUT| Sets LED Colour & Brightness	|
SUPERVISOR	|Q3		|STUDENT_PIXEL_EN| HIGH			| Enables Student Control, Blocks Supervisor Control		|



### Power Output Connectors

| Voltage/Bus 		| Purpose/Name	| Component Number 	| Connector Type 	| Current Considerations 	|
|---				|---			|---				|---				|---						|
| 12V				| 12V_DC		|		J30			| Screw Terminal	| Unregulated ~8A Max(For entire Bus)|
| 12V				| Strip Lighting| 		J4			| Molex				| Unregulated ~8A Max(For entire Bus)|
| 12V       		| DC MOTOR PWR	|		J16			| Screw Terminal	| Unregulated ~8A Max(For entire Bus)|
| 5V_DC_LED			| 5V_DC_LED		| 		J6			| Screw Terminal	| 1A Total. Regulated	|
| 5V_DC_RPI			| 5V_DC Spare	| 		J31			| Screw Terminal	| 2.5A Total. Regulated	|
| 5V_DC_RPI			| USB Power		| 		J5			| USB A Socket x2	| 2.5A Total. Regulated	|

#### Additional Voltage Bus Connections

Additional headers have been provided for:
- 3V3 DC Power Output (1A Max)
- 5V DC Digital Power Output (2 - 2.5A Max, including USB Socket)
- 5V DC Servo Power Output (1A Max)
- 12V DC Bus (Unregulated - 6A Max)

These are intended for future use, fault finding or reconfirging PCBs to perform tasks outside of the specified use cases.

### Thermocouple

__Currently Unavailable due to parts shortages__

To use Thermocouple Input with any configuration, the following external hardware should be connected as follows:

- K-Type Thermocouple, connected to __J22 Thermocouple__ connector.


__Thermocouple input __J22 Thermocouple__ requires IC __U19 AD8497__ To be populated. (UNTESTED)__

Analog voltage is buffered and distributed to both MCUs, __Pin A3__






