/* supervisor Test Firmware

  Written BY:

    Imogen Wren
    Bhavith MANAPOTY
    Eralp CALHAN
    14.06.2022

  Test firmware contains libraries suitable for testing all hardware
*/

#include <autoDelay.h>

#include "supervisor_pinMap.h"    // PinMap for Supervisor pcb - Supervisor MCU

#include "testSettings.h"       // settings page sets up active functions for each test

#include "basicFunctions.h"       // Basic functions like pin reads that didnt need an entire page

#include "shiftFunctions.h"       // Shiftregister functions (defined outside the library and specific to this project)

#include "dcMotorFunctions.h"     // DC Motor Functions

#include "encoderFunctions.h"     // Optical Encoder functions

#include "stepperFunctions.h"     // Stepper Motor Functions

#include "servoFunctions.h"       // Servo Motor Functions

#include "pixelFunctions.h"        // WS2821b LED functions


/* Test Settings

    Enable and disables various functions to test hardware function by function


*/
#define STUDENT_MOTOR_ENABLE      true                     // Software Tested
#define STUDENT_STEPPER_ENABLE    true                     // Software Tested
#define STUDENT_PIXEL_ENABLE      true                     // Software Tested

#define SHIFTREG_OVERWRITE        0b00000000                // Software Tested

#define DC_MOTOR_ENABLE           false                    // Software Tested
#define DC_MOTOR_CLOCKWISE        false                     // Tested but difficult to prove without actual hardware due to amount of hardware logic introduced
#define DC_MOTOR_SPEED            0                      // Software Tested
#define DC_CURRENT_SENSE_ACTIVE   false                    // Software Tested - Maths might not be correct but gives (some) usable(ish) data

#define ENCODER_ACTIVE            false                    // Tested Working but maths not accurate

#define STEPPER_ENABLE            false                      // Enable pin now controlled from stepper function not independently
#define STEPPER_CLOCKWISE         false                     // Stepper direction now controlled from stepper function not independently
#define STEPPER_RESET             false                     // Software Tested // Must be hight to enable  


#define STEPPER_ACTIVE            false                    // Software TEsted
#define NUM_REVOLUTIONS           2
#define STEPPER_FAULT_ACTIVE      false                     // Tested


#define SERVO_ACTIVE              false                     // Tested

#define STUDENT_SERVO_DETECT      false                     // Needs Testing with 2nd MCU

#define PIXEL_ACTIVE              false                     // Software Tested

#define LIMIT_SWITCH_ACTIVE       false                    // Tested

void setup() {

  Serial.begin(115200);
  while ( !Serial ) delay(10);   // Might be required for Nano IoT 33

  // LED BUILTIN
  ledBegin();

  // ShiftRegister and Enable Pins
  shiftReg.begin();   // Begin opens serial comms and sets shiftReg data pins to output
  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();   // Prints the current state of the shiftregister to serial monitor for debugging

  // The first way to use this API is to write functions for a specific device or channel we wish to enable or disable
  studentMotorEN(STUDENT_MOTOR_ENABLE);
  studentStepperEN(STUDENT_STEPPER_ENABLE);
  studentPixelEN(STUDENT_PIXEL_ENABLE);
}
void loop() {
  if (STUDENT_MOTOR_ENABLE)
    studentDCdirectionDectect();
    
  studentMotorEN(STUDENT_MOTOR_ENABLE);
  studentStepperEN(STUDENT_STEPPER_ENABLE);
  studentPixelEN(STUDENT_PIXEL_ENABLE);
  
  Serial.println("Student Motor Enabled");
  Serial.println("Student Stepper Enabled");
  Serial.println("Student LED Enabled");
  delay(13000);
  Serial.println("Student Motor Disabled");
  studentMotorEN(false);
  delay(5000);
  delay(7000);
  Serial.println("Student Stepper Disabled");
  studentStepperEN(false);
  delay(9000);
}
