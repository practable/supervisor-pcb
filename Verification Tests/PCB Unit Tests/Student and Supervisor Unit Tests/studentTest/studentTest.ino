/* student Test Firmware

  Written By:
    Imogen Wren
    Bhavith MANAPOTY
    Eralp CALHAN
    14.06.2022

  Test firmware contains libraries suitable for testing all hardware
*/

#include <autoDelay.h>

#include "student_pinMap.h"    // PinMap for Supervisor pcb - Supervisor MCU

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

#define SHIFTREG_OVERWRITE        0b00000000                // Software Tested

#define DC_MOTOR_ENABLE           true                    // Software Tested
#define DC_MOTOR_CLOCKWISE        true                    // Tested but difficult to prove without actual hardware due to amount of hardware logic introduced
#define DC_MOTOR_SPEED            30                       // Software Tested
#define DC_CURRENT_SENSE_ACTIVE   false                     // Software Tested - Maths might not be correct but gives (some) usable(ish) data

#define ENCODER_ACTIVE            false                     // Tested Working but maths not accurate

#define STEPPER_CLOCKWISE         true                     // Software Tested
#define STEPPER_RESET             true                     // Software Tested    // Must be high to enable


#define STEPPER_ACTIVE            true                     // Half Tested - Needs Testing  // Pulse is stopped but motor still runs!? Doesnt if pulse pin tied top GND or Vcc - Because magic smoke Released?
#define STEPPER_DELAY_mS          500                       // Software Tested
#define STEPPER_FAULT_ACTIVE      false                     // Tested


#define SERVO_ACTIVE              true                     // Tested but no control


#define PIXEL_ACTIVE              true                     // Software Tested
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

  // DC Motor Control
  dcMotorBegin();              // Set control pins to output
  dcMotorEnable(DC_MOTOR_ENABLE );        // Need shift Register to enable board
  dcMotorDirection(DC_MOTOR_CLOCKWISE);      // Set DC Motor Direction
  dcMotorSpeed(DC_MOTOR_SPEED);             // Set DC Motor Speed   - default off

  // Stepper Motor Control
  stepperBegin();
  stepperDirection(STEPPER_CLOCKWISE);
  stepperReset(STEPPER_RESET);

  // Servo Motor Control
  servoBegin();                          // begin Servo functions
  servoConstrain(-180, 180);             // Constrain min max travel for servo position

  // WS2821b Pixel LED Control
  pixelBegin();
}





void loop() {
  //MOTOR TEST
  Serial.println("MOTOR TEST: (12s)");
  Serial.println("STUDENT ENABLED");
  Serial.println("CLOCKWISE");
  dcMotorSpeed(DC_MOTOR_SPEED);
  delay(5000);
  dcMotorSpeed(0);
  dcMotorDirection(!DC_MOTOR_CLOCKWISE);
  delay(2000);
  Serial.println("ANTI-CLOCKWISE");
  dcMotorSpeed(DC_MOTOR_SPEED);
  delay(5000);
  dcMotorSpeed(0);
  delay(3000);
  Serial.println("REPEAT TEST WITH STUDENT DISABLED");
  Serial.println("CLOCKWISE");
  dcMotorSpeed(DC_MOTOR_SPEED);
  delay(1000);
  dcMotorSpeed(0);
  dcMotorDirection(!DC_MOTOR_CLOCKWISE);
  delay(1000);
  Serial.println("ANTI-CLOCKWISE");
  dcMotorSpeed(DC_MOTOR_SPEED);
  delay(1000);
  dcMotorSpeed(0);
  delay(1000);

  //=================================================

  //STEPPER MOTOR UNIT TEST
  Serial.println("STEPPER TEST:");
  stepper_test(STEPPER_ACTIVE);

  //=================================================
}
