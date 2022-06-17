
# Remote Labs Supervisor PCB v1.0 Testing Documentation

## Hardware Changes and Tests:

### Modifications Made to Board:
1. Trace from U13 Pin 8 to Stepper Motor Driver Enable Pin (A4 Pin 1) was cut.
2. Trace from 3.3V to Optical Encoder was cut.
3. Optical Encoder power is now supplied from a 5V bus.
4. U13 Pin 8 is now connected to Stepper Motor Driver Sleep Pin (A4 Pin 6).
5. Pullup resistors were added to the buffers U20, U21, U22. New buffers which do not need pullup resistors have been ordered. Resistors have been added to Pins 2,4,6,8,10,12 of each buffer.

### Test 1: Smoke Test (Without Valuable Components)
Connect power supply to the PCB (with no valuable components connected) and check if smoke is released from any part of the board.

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Smoke Test|Check if smoke is releases when power supply is connected|No smoke released   |

### Test 2: Check Voltages:
Connect power supply to the PCB and measure the voltages at the following points. Ensure not to connect any valuable components.
- J31 - 5V Pin
- J30 - 12V Pin
- A3 - VBAT
- J6 - 5V Pin
- J34 - 5V Bus
- J33 - 12V Bus
- J35 - 5V Bus
- J36 - 3.3V Bus
- A4 - Pin 16

Expected Observations:
|Pin|Expected Output|
|---|---------------|
|A3 - VBAT|~12V|
|A4 - Pin 16|~12V|
|J6 - 5V Pin|~5V|
|J30 - 12V Pin|~12V|
|J31 - 5V Pin|~5V|
|J33 - 12V Bus|~12V|
|J34 - 5V Bus|~5V|
|J35 - 5V Bus|~5V|
|J36 - 3.3V Bus|~3.3V|

### Test 3: Smoke Test (With Valuable Components)
Connect all valuable components to the PCB and then connect the power supply to the PCB. Check if smoke is released from any part of the board.

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Smoke Test|Check if smoke is releases when power supply is connected|No smoke released   |

### Test 4: Check Voltages:
Repeat Test 2 after connecting all components to ensure the results are the same.

## Supervisor Software Tests: 

### Test 5: Supervisor Limit Switch Test:
Connect the Supervisor Arduino Nano 33 IoT to the PCB. Connect the Limit Switch to the PCB. Upload the code from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Supervisor%20Tests/Limit%20Switch%20Test/supervisorTest/supervisorTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Limit Switch Test|Press Limit Switch during runtime|Serial Print should read "Limit Switch Pressed"   |

### Test 6: Supervisor LED Test:
Connect the Supervisor Arduino Nano 33 IoT to the PCB. Connect the LED to the PCB. Upload the code from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Supervisor%20Tests/LED%20Test/supervisorTest/supervisorTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|LED Test|LED Test|LED should switch on and change colors in a breathing pattern|

### Test 7: Supervisor Stepper Motor Test:
Connect the Supervisor Arduino Nano 33 IoT to the PCB. Connect the Stepper Motor to the PCB. Upload the code from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Supervisor%20Tests/Stepper%20Test/supervisorTest/supervisorTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Stepper Motor Test|Stepper Motor Test|Stepper motor should make two whole rotations in one direction, wait for 2 seconds, and then make two rotations in the other direction. This should keep repeating.|
**NOTE: The motor should only draw current when it is rotating and not when it is still. If there is current being drawn at all times, the motor will get extremely hot.**

### Test 8: Supervisor DC Motor Test:
Connect the Supervisor Arduino Nano 33 IoT to the PCB. Connect the DC Motor to the PCB. Upload the code from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Supervisor%20Tests/Motor%20Test/supervisorTest/supervisorTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|DC Motor Test|DC Motor Test|DC Motor should rotate in the given direction (from the code) at the given speed (from the code)|
Repeat this test changing the direction and motor speed in the code to verify that it works.

**NOTES:**
1. Do not increase speed over 100 as it is a very powerfull motor.
2. If the direction of rotation is incorrect from the code, the wires of the motor may be dconnected to the PCB in the wrong way. To fix this, intercahnge the orientation of the wires on the PCB.

## Supervisor and Student Software Tests:
### Test 9: Full Software LED Test:
This test checks if the student can control the LED. It also checks whether the supervisor can enable and disable control access for the student.
#### Supervisor Allowing Student to Control LED:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the LED to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/LED%20Test/Supervisor%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/LED%20Test/Supervisor%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|LED Test|LED Test|Student should be allowed to control LED. Hence LED should be switched on|
#### Supervisor NOT Allowing Student to Control LED:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the LED to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/LED%20Test/Supervisor%20Not%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/LED%20Test/Supervisor%20Not%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|LED Test|LED Test|Student should not be allowed to control LED. Hence LED should be switched off|

**Final Test Observations:**
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Supervisor and Student LED Test|Supervisor and Student LED Test|Supervisor should be able to enable and diable LED control access to the student|

### Test 10: Full Software DC Motor Test:
This test checks if the student can control the DC Motor. It also checks whether the supervisor can enable and disable control access for the student.
#### Supervisor Allowing Student to Control Motor:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the DC Motor to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Motor%20Test/Supervisor%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Motor%20Test/Supervisor%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Motor Test|Motor Test|Student should be allowed to control motor. Hence the motor should be rotating in the given direction and given speed in the Student Code|
#### Supervisor NOT Allowing Student to Control Motor:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the Motor to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Motor%20Test/Supervisor%20Not%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Motor%20Test/Supervisor%20Not%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Motor Test|Motor Test|Student should not be allowed to control motor. Hence the motor should be switched off|

**Final Test Observations:**
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Supervisor and Student Motor Test|Supervisor and Student Motor Test|Supervisor should be able to enable and diable motor control access to the student|

### Test 11: Full Software Stepper Motor Test:
This test checks if the student can control the Stepper Motor. It also checks whether the supervisor can enable and disable control access for the student.
#### Supervisor Allowing Student to Control Stepper Motor:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the Stepper Motor to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Stepper%20Test/Supervisor%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Stepper%20Test/Supervisor%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Stepper Motor Test|Stepper Motor Test|Student should be allowed to control stepper motor. Hence the stepper should be rotating in the given direction for the given number of rotations in the Student Code|
**NOTE: The motor should only draw current when it is rotating and not when it is still. If there is current being drawn at all times, the motor will get extremely hot.**
#### Supervisor NOT Allowing Student to Control Stepper Motor:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the Stepper Motor to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Stepper%20Test/Supervisor%20Not%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Stepper%20Test/Supervisor%20Not%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Stepper Motor Test|Stepper Motor Test|Student should not be allowed to control Stepper Motor. Hence the stepper should be switched off|
**NOTE: The motor should only draw current when it is rotating and not when it is still. If there is current being drawn at all times, the motor will get extremely hot.**

**Final Test Observations:**
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Supervisor and Student Stepper Motor Test|Supervisor and Student Stepper Motor Test|Supervisor should be able to enable and diable stepper motor control access to the student|

### Test 12: Full Software Servo Test:
This test checks if the student can control the Servo. It also checks whether the supervisor can enable and disable control access for the student.
#### Supervisor Allowing Student to Control Servo:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the Servo to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Servo%20Test/Supervisor%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Servo%20Test/Supervisor%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Servo Test|Servo Test|**NEEDS TO BE WRITTEN**|

#### Supervisor NOT Allowing Student to Control Servo:
Connect both Arduino Nano 33 IoT boards to the PCB. Connect the Servo to the PCB. 
Upload the code for the supervisor from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Servo%20Test/Supervisor%20Not%20Allowed/supervisorTest/supervisorTest.ino).
Upload the code for the student from [here](https://github.com/ImogenWren/RemoteLabs_Supervisor_PCB/blob/main/Verification%20Tests/PCB%20Unit%20Tests/Servo%20Test/Supervisor%20Not%20Allowed/studentTest/studentTest.ino).

Expected Observations:
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Servo Test|Servo Test|**NEEDS TO BE WRITTEN**|

**Final Test Observations:**
|Test      |Description                                           |Expected Observation|
|----------|------------------------------------------------------|--------------------|
|Servo Test|Servo Test|**NEEDS TO BE WRITTEN**|

## Final Software Tests
### Test 13: Test all Software with All Components Plugged In
Repeat all Supervisor and Student software tests with all components plugged in. All tests should result in the same observations.

## Tests Pass/Fail:
**NOTE: For the Pass/Fail badges, use one of the following:**
https://img.shields.io/badge/Tests-PASS-success
https://img.shields.io/badge/Tests-FAIL-red
https://img.shields.io/badge/Tests-TESTING-lightgrey


|Test|Pass/Fail|
|----|---------|
|Test 1|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 2|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 3|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 4|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 5|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 6|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 7|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 8|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 9|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 10|![](https://img.shields.io/badge/Tests-FAIL-red)|
|Test 11|![](https://img.shields.io/badge/Tests-PASS-success)|
|Test 12|![](https://img.shields.io/badge/Tests-TESTING-lightgrey)|
|Test 13|![](https://img.shields.io/badge/Tests-TESTING-lightgrey)|

## Errors and Bugs Recorded:
1. While uploading code to the Arduino Boards, sometimes the DC Motor spins at full speed. This is potentially due to a PWM Signal being given to the motor pins during upload.
2. While uploading code to the Arduino Boards, sometimes the Stepper Motor rotates for 1 microstep in each direction continuously. This is potentially due to a PWM Signal being given to the stepper pins during upload.
3. While testing the DC Motor, the student is unable to control direction as the Supervisor is unable to perform a digitalRead on Analog Pins A0 and A1. These pins always read LOW even when the voltage on the pins is HIGH. This potentially due to an AnalogRead being called on those pins at some point in the code which causes the digitalRead values to be overwritten (This anamoly is tested and could potentially be the reason for the bug)