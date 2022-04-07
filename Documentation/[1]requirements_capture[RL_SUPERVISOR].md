# [1]   Requirements Capture Form - [RL_SUPERVISOR]

_This form is intended to assist in capturing the requirements for new Open Source Embedded Systems Projects, <br>
its scope & implementation can be adapted to suit projects of varying complexity._

***************************************************************************************************************************************************************
## [1.1]Project Brief
_The project brief should contain an outline of the proposed project, with enough detail to derive a comprehensive list of requirements. The format, layout and
information provided can be tailored to project complexity_


### Project Brief - [RL_SUPERVISOR]

Design a PCB to provide power to remote labs experiments, which involve students programming microcontrollers remotely.
PCB should also provide a supervisory role, blocking actuation of experimental hardware if it is likely to cause damage to the equipment.

This allows students to upload their own code to a bare bones microcontroller, without risk of causing hardware damage or unsafe conditions.

#### Current State

~70 remote labs experiments, each requiring:
- 12v supply for motors
- 12v supply for LED lighting
- 5v supply for Raspberry Pi
- 5v supply for Microcontrollers
- 5v supply for 5 port switch

Power Provisions:

12vDC PSU, daisy chained power to 4 x Experiment Boxes

Comms:

5 Port switch in one box, ethernet comms from each box in the stack of 5 meet there for connection to LAN

#### Experiment Description

##### Spinner

- 	DC Motor & Controller
- 	Optical Encoder
- 	Temperature Sensor

Encoder needs calibration on power up.

##### Digger

As ***Spinner*** Plus:

-	Servo - CS238MG (4.8 - 6.0v)
- 	Limit switches? Probably not

Encoder calibrated then used to limit movement of DC motor.
Servo position limited to avoid collision.

Servo blocked from actuation while digger is moving, and vice versa.


##### Govenor

As ***Spinner*** Plus:

- Stepper Motor
- 2x limit switches (1 definite, 1 potential) - OR gate for virtual/spoof limit switch

Limit switches limit movement of stepper motor.

Stepper motor blocked from actuation while govenor is in motion and vice versa.


##### Pendulum

5v Electromagnet with 4 possible states:

-	Open Circuit
-	Closed Circuit - direct short via transistor BC547 & flyback diode
	- #TODO Research: dual transitor pass gate. - Simulate?
-	Energised (Positive Direction)
- 	Energised (Negative Direction)

-	600ppr Optical Encoder

-	Temperature sensor?

### Features & Functions of the New System

#### Supervisor MCU Requirements
Concept:
_Supervisor MCU manages system, performs its own calibrations to track experiment status and monitor for actions that could damage the apparatus_

[X]	-	SAMD21 MCU IC
[X]	- 	Encoder Calibration 
		- devolved requirement: Must control motor actuation during this process.
[X]	- 	Logic to prevent both Supervisor and Student Controllers from actuating hardware at the same time.
[X]	-	Depower motors & other actuators and alert user if temperature is approaching max: (90degC)?
[X]	-	Track & Report encoder Position & velocity independent of STUDENT MCU.
[X]	-	Cut power to DC motor in case of out of bounds operation for experiments that require this function.
[X]	-	Set boundaries of operation for Servo motor. Cut power/control if limits breached.
[X]	- 	Set hard limits of operation for stepper motor using limit switches. Alert the user & cut stepper motor if switches are actuated.
[X]	-	Prevent actuation of the servo while the rotating platform is in motion. Prevent platform rotation if servo is in motion.
[X]	- 	Prevent actuation of stepper motors if govenor is in motion. Prevent govenor rotation if stepper motor is in motion.
[X]	-	Note: in any case where power is cut to hardware, supervisor MCU must be capable of resetting the experimental apparatus to a stable "home" position and return control to the student MCU.
[X]	- 	Virtual Limit switches for students

##### Student MCU Requirements
Concept:
_Bare metal programming experience - The student should have full control of the MCU, the supervisor MCU is responsible for protecting the rest of the experimental apparatus from damage._

[X] -	SAMD21 MCU IC
- 	

- Control all experimental hardware i.e:
[X]	-	DC Motor Via Motor Controller
[x]	- Servo Via PWM output
[x]	- Stepper motor via Stepper Motor Controller.
[x]	- Electromagnetic actuator.
[x]	- Temperature Sensor?


##### Servo Control

- 	Detect PWM from Student PCB? 
-	Frequency Counter?
-	Seperate controller for high frequency signal aquisition.?
-	Op amp filtering into comparator ? - probably not , temperature issues, tuning, calibration.



#### Example Logic

#### Power Supply Requirements





#### Sub-Systems Specifications
##### Power Requirements Per Experiment
_Specific requirements for subsystems can be documented at this stage_    <br>
> a. steady power usage of 20W 1.7A at 12V (Maxxon AMax 32 236668 Graphite brushes, 20 Watt)[Estimated value, may change in future iterations] <br>
> b. peak power usage of 69W 5.7A at 12V (when motor stalled)  [Estimated value, may change in future iterations] <br>
> c. 5V power for the Raspberry pis, typically 1A per Raspberry Pi but Max 2.5A.


##### Interface Requirements

 


#### General Specifications/Requirements
_These specifications are going to be valid for most projects developed using this framework_
> 4. Circuit should be protected from reverse supply voltages. <br>
> 5. Circuit should be fuse protected <br>



#### Optional Features
_Any features or functions that are optional should be stated here_  <br>
>  1. Report Status & current usage for sustainabilty and maintainance purposes.  #NOTE: do we want to include this feature?
>  3. Use only connection types that can be operated with one hand. i.e. avoid screw terminals.


#### Design Optimisation
_What parameters of the design should be minimised/maximised?_




#### Design Tradeoffs
_Space for discussion and weighing up of features that may or may not be required_ <br>



### Modular System Potential

##### DC Motor Controller

- COTS
- Integrated

##### Stepper Motor Controller

- COTS
- Integrated

##### Pendulum Electromagnet

- Motor Controller?
- Integrated driver
- Daughterboard replacement

IF integrated:
On main PCB or Daughterboard?

Could 1 PCB be reconfigured for each experiment using daughterboards?


#### Motor Controller Options

Infineon DC Motor Sheild
https://uk.rs-online.com/web/p/shields-for-arduino/9062874?

L298N Dual Full Bridge Driver
https://docs.rs-online.com/6243/0900766b80060c26.pdf

Can drive stepper motors & DC Motors.

######## Current Guvnor Experiement PCB

DC Motor:
[Pmod HB3: H-bridge Driver with Feedback Inputs](https://digilent.com/shop/pmod-hb3-h-bridge-driver-with-feedback-inputs/)

Stepper Motor:
[DRV8825 Module](https://printermods.co.uk/products/sku10919)









### Supervisor Controller Circuit Topology

#### Problem

System must allow clear differentiation between STUDENT mcu involved in running experiment, and SUPERVISOR MCU which manages the system and supervises the STUDENT MCU, while programming remotely.

###### Option A

Student & Supervisor MCU both have dedicated CH340 USB interface. Select CH340 with programmable PID identifier to allow Raspi software to roboustly identify the STUDENT and SUPERVISOR MCUs using PIDs.
	Disadvantages:
	- Sourcing correct5 CH340 USB interface chip

##### Option B

STUDENT MCU has no direction USB interface, is programmed from SUPERVISOR MCU.
	Disadvantages:
	- Increase complexity of firmware requirements for Supervisor

##### Option C

SUPERVISOR MCU is programmed via UART from the raspberry pi - tested and proven on bench
STUDENT MCU is programmed via CH340 interface and USB, maintaining a familiure interface for students who may be interacting with the microcontroller

##### Option D

Both MCUs are programmed via USB, but supervisor MCU has a handshake procedure that responds to a specific data packet to "prove" it is the supervisor MCU

# DECISIONS THAT NEED TO BE MADE


- Stepper motor voltage - check specifications. Check current drivers.


- Servo PWM monitoring?


# DECISIONS THAT have been MADE

- 5v Power Supply - lM2589 Modules 2.5A max?
- Independent 12v to 5v PSU for servos.
- DC Motor - 12v - Infineon board

- MCU CH340 for Student
- Supervisor programmed directly from UART. 

- ISPs & UART For supervisor
- ISP & CH340 for student







#### Quality Assurance 
_What quality assurances or requirements, if any, need to be established?_

#### Notes
_Any Extra Notes?_

Software Reqirements: 




#### Concept
_Outline any concept or topology that may be worth exploring._

System Concept:

##### Power Distribution:









### Existing Products & COTS (Consumer Off The Shelf)
_The project brief may also contain information on currently available similar products and a brief description of the features they lack and a 
quick review of whether they can fullfill the aims of the project._


_______________________________________________________________________________________________________________________________________________________
## [1.2]High Level Requirements Description

*This section should contain a numbered list of all the specific high level requirements that can be gathered from the project brief, or from the client directly. <br>
High Level Requirements capture the intent and function of a system, without going into specifics of how these will be achieved or any specific implementations. I.E. They take a Black Box approach*

#### High Level Requirements should address:
> - Client Needs
> - Features & Functionality
> - Interfaces
> - Performance
> - Quality Attributes
> - Design Constraints
> - Regulations
> - Safety & Security
> - System

#### Requirements should be:
> - Specific           - Document a single feature or function requirement at a time.                                                 <br>
> - Quantifyable       - Provide quantifyable parameters, boundary limits of operation and/or design tolerences, rather than open ended specifications where possible.<br>
> - Self Contained     - Do not rely on assumptions to deliver information, as different engineers will make different assumptions, which may cause conflicts.
> - Traceable          - Assign each requirement an ID number, this will be used to trace any design decisions through the development process. <br>

_Good requirements are the foundation for successful development of a project, as it allows design decisions to be traced through the development process.
it also provides the information required to undertake successful **Verification** & **Validation**[^V&V]._ 


_______________________________________________________________________________________________________________________________________________________
## [1.3]Requirements Capture - [RL_SUPERVISOR]

| ID	| Sub-System 		| Requirement/Function 								| Notes												|
|---	|---				|---												|---												|
| R.1	| Supervisor MCU	| SAMD21											|													|
| R.2	| Supervisor MCU	| Encoder Calibration								|													|
| R.3	| Supervisor MCU	| Tracking Of Encoder position throughout experiment|													|
| R.4	| Supervisor MCU	| Prevent overheating of experimental apparatus 	|													|
| R.5	| Supervisor MCU	| Enable/Disable stepper motor function 			| TODO: Does it also need control of stepper motor? - Yes in order to reset it |	
| R.6	| Supervisor MCU	| Enable/Disable Servo actuation 					| TODO: Does it also need control of servo at all?	- Yes in order to reset it |	
| R.7	| Supervisor MCU	| Enable/Disable DC Motor control for Student & Supervisor	| Ensure that only 1 MCU is in control of actuators at any point in time	|
| R.8	| Supervisor MCU	| Provide soft or Virtual limits on DC motor movement		|											|
| R.9	| Supervisor MCU	| Provide soft or Virtual limits on Servo actuation to prevent out of bounds operation		|			|
| R.10	| Supervisor MCU	| Provide soft or Virtual limits on stepper motor actuation to prevent out of bounds operation			|	
| R.11	| Supervisor MCU	| Provide hard limits on stepper motor actuation to prevent out of bounds operation using limitswitches		|			|
| R.12	| Supervisor MCU	| Provide hard limits on stepper motor actuation to prevent out of bounds operation using limitswitches		|			|
| R.13	| Supervisor MCU	| Block actuation of Servo/Stepper if DC motor is moving & vice versa |	Priority given to the first thing moving? OR Priority given to DC Motor?|
| R.14	| Supervisor MCU	| Reset experiment to neutral condition in the case limits are breached |								|
| R.15	| Supervisor MCU	| Track Motor Driver PCB Temperature via over temp output|													|	


|---	|---				|--- 												|---												|
| R.15	| Student MCU		| SAMD21											|													|
| R.16	| Student MCU		| Control over experimental hardware inc; DC Motor, Stepper Motor, Servo & Electromagnetic Actuator	|	|
| R.17	| Student MCU		| Direct access of encoder feedback data			|													|
| R.18	| Student MCU		| Direct or Virtual access of temperature sensor	|													|
| R.19	| Student MCU		| Virtual access of Limit switch data (spoofed from Supervisor MCU)	|									|
| R.20	| Student MCU		| Bare Bones Programming Experience  				|		Can this be quanfied in some way?			|

|---	|---				|--- 												|---												|
| R.21	| Power Supply		| 5v Power @ 0.5A max for MCUs						|													|
| R.22	| Power Supply		| 5v Power @ 2.5A max for Raspberry Pi				|													|
| R.23	| Power Supply		| 5v Power @ 2.5A max for Servo						|													|
| R.24	| Power Supply		| 12v Power Distribution for DC Motor Driver		|													|
| R.25	| Power Supply		| 12v Power Distribution for Stepper Motor Driver	|													|

|---	|---				|--- 												|---												|
| R.21	| Sensors			| Temperature Sensor to track motor temperature		|													|
| R.22	| Sensors			| Limit Switch Inputs (x2 definatly) (2x spare/Future Use?)		|													|
| R.23	| Sensors			| Optical Encoder - Distributed via buffers to both MCU	|													|
| R.24	| Sensors			| 12v Power Distribution for DC Motor Driver		|													|
| R.25	| Sensors			| 12v Power Distribution for Stepper Motor Driver	|													|	

#TODO 
Define relationship between servo and MCU control - how is that going to be tracked?


## Devolved Requirements
_Requirements that are established to meet higher level requirements_

| ID	| Sub-System 		| Requirement/Function 		| Devolved Requirement														| Hardware/Software Requirement	|
|---	|---				|---						|---																		|---							|
| DR.2.1| Supervisor MCU	| Encoder Calibration		| Prevent Student MCU from actuating motor while calibration is undertaken	| Both 							|
| DR.2.2| Supervisor MCU	| Encoder Calibration		| Enable supervisor MCU to actuate motor while calibration is undertaken  	|	 Both							|
| DR.3.1| Supervisor MCU	| Tracking Encoder			| Duplcation of digital encoder signals to feed both MCU's					|  Hardware						|
| R.3	| Supervisor MCU	| Encoder Calibration		| Hardwired logic to enable & disable control of motor. Buffers to duplicate digital signal from encoders|	Run calibration on startup or via remote API|



- 	Encoder Calibration 
	- devolved requirement: Must control motor actuation during this process.

- 	Logic to prevent both Supervisor and Student Controllers from actuating hardware at the same time.

-	Depower motors & other actuators and alert user if temperature is approaching max: (90degC)?

-	Track & Report encoder Position & velocity independent of STUDENT MCU.

-	Cut power to DC motor in case of out of bounds operation for experiments that require this function.

-	Set boundaries of operation for Servo motor. Cut power/control if limits breached.

- 	Set hard limits of operation for stepper motor using limit switches. Alert the user & cut stepper motor if switches are actuated.

-	Prevent actuation of the servo while the rotating platform is in motion. Prevent platform rotation if servo is in motion.

- 	Prevent actuation of stepper motors if govenor is in motion. Prevent govenor rotation if stepper motor is in motion.

-	Note: in any case where power is cut to hardware, supervisor MCU must be capable of resetting the experimental apparatus to a stable "home" position and return control to the student MCU.

- 	Virtual Limit switches for students






When to review? <br>
*High level requirements should undertake a review process,* ***Validation***, *to ensure they meet the clients needs, before any further development takes place.*<br> 

<!--After review, please see the next document in the design process* [[2]Low Level Requirements Capture](https://github.com/PanGalacticTech/project_template/blob/main/%5B2%5DLL_requirements_capture.md) -->


_______________________________________________________________________________________________________________________________________________________



[^V&V]: Verification & Validation - What is it? <br>
        - Verification - _"Does the implementation meet the requirements?"_ <br>
        - Validation   - _"Are the requirements correct"_
        
[^2]: Assumption made that only 1 motor will be in stall condition, with others running typically.
