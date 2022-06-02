# Remote Labs Supervisor PCB Verification Firmware

_This folder contains a range of firmware options to enable verification testing of all the functions of the Supervisor PCB._ <br>

As there is a few different ways the PCB can be populated, for the time being all pin references are assuming that the board will be used with Arduino Nano IoT 33 as the MCU, and shift registers
are installed to expand the number of IO pins.


## Pin Declarations

_Pin Declarations, references and Functions can be found in the Excel Spreadsheet Supervisor_PCB_PinMap_

This is used to generate 2 header files:

supervisor_pinMap.h
student_pinMap.h

which will list all IO pins referencing their arduino pin numbers with the PCB pin name. 






## Functions to Test

### Sensor Inputs

[x] if included in program

- Optical Encoder															 	[x]
- Limit Switches (1 )															[x]
- Thermocouple [Unavailable due to component supply]							[ ]
- Motor Driver Current 1														[X]
- Motor Driver Current 2														[X]
- Stepper Motor Fault Detect													[X]
- Student to Supervisor Servo Detection											[x]


_All sensor inputs are mirrored over each MCU, therefore the same software written to test the data aquisition can be programmed into both MCUs and measurements compared._

_Note: There will be some discrepancy between readings due to additional Current Limiting Resistors between the AI pins of the student MCU and the signal distribution amplifyers/buffers. 
the difference between the two ADC Readings can be used as a small focus for experimentation_

For Motor Driver Current 1 and 2, Motor speed will be controlled via supervisor, while current readings are taken on both MCUs

For Optical Encoder testing, motor will be unpowered and the encoder manipulated by hand.


#### Supervisor

#### Student

### Actuator Outputs
_Note: To fully test the actuator outputs, supervisor MCU must enable outputs for student MCU_

#### Supervisor

- LED_BUILTIN  (Pin D13 - SCK) 													[x]
- DC Motor																		[x]	
- Stepper Motor																	[x]														
- Servo Motor																	[x]
- WS2812B LEDs																	[x]


#### Student

- LED_BUILTIN   (Pin D13 - SCK)                                                    [x]
- DC Motor																			[]
- Stepper Motor																		[]
- Servo Motor - Via analogRead on supervisor (Translate to output for test?)		[]
- WS2812B LEDs																		[]

#### Supervisor Output Control
_Test each enable pin seperatly to confirm control by student is blocked_

- Student DC Motor Enable														[x]
- Student Stepper Motor Enable													[x]
- Student Pixel Enable															[x]

- Student to Supervisor Servo 1													[]




## Power & Other PCB Functions
_Test that do not require MCUs to test function_

- 12v Bus Voltage
- 5V Power Bus Voltage
- 5v Raspi Bus Voltage
- USB power of MCUs [Requires cutting trace on PCB]
- 3v3 MCU Bus Voltage
- Power LEDs showing for 12v and for 3v3.
-


## Test Firmware Details


supervisorTest.ino

studentTest.ino

Each program contains all the functions to cross test all hardware, a config file can be generated for each test which will set each function for that test.





