/* supervisor Unit Test Firmware

  Written BY:

    Imogen Wren
    Bhavith MANAPOTY
    Eralp CALHAN
    14.06.2022

  Unit Test Firmware that tests DC Motor, Stepper Motor, LED, Optical Encoder and Limit Switch.
  
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
#define STUDENT_MOTOR_ENABLE      false                     // Software Tested
#define STUDENT_STEPPER_ENABLE    false                     // Software Tested
#define STUDENT_PIXEL_ENABLE      false                     // Software Tested

#define SHIFTREG_OVERWRITE        0b00000000                // Software Tested

#define DC_MOTOR_ENABLE           true                    // Software Tested
#define DC_MOTOR_CLOCKWISE        true                     // Tested but difficult to prove without actual hardware due to amount of hardware logic introduced
#define DC_MOTOR_SPEED            30                      // Software Tested
#define DC_CURRENT_SENSE_ACTIVE   false                    // Software Tested - Maths might not be correct but gives (some) usable(ish) data

#define ENCODER_ACTIVE            true                    // Tested Working but maths not accurate

#define STEPPER_ENABLE            true                      // Enable pin now controlled from stepper function not independently
#define STEPPER_CLOCKWISE         true                     // Stepper direction now controlled from stepper function not independently
#define STEPPER_RESET             true                     // Software Tested // Must be hight to enable  


#define STEPPER_ACTIVE            true                    // Software TEsted
#define NUM_REVOLUTIONS           2
#define STEPPER_FAULT_ACTIVE      false                     // Tested


#define SERVO_ACTIVE              false                     // Tested

#define STUDENT_SERVO_DETECT      false                     // Needs Testing with 2nd MCU

#define PIXEL_ACTIVE              true                     // Software Tested

#define LIMIT_SWITCH_ACTIVE       true                    // Tested

void setup() {
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // Might be required for Nano IoT 33

  // LED BUILTIN as OUTPUT
  ledBegin();

  // ShiftRegister and Enable Pins
  shiftReg.begin();   // Begin opens serial comms and sets shiftReg data pins to output
  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();   // Prints the current state of the shiftregister to serial monitor for debugging

  // DC Motor Control
  dcMotorBegin();              // Set control pins to output
  dcMotorEnable(DC_MOTOR_ENABLE );        // Need shift Register to enable board
  dcMotorDirection(DC_MOTOR_CLOCKWISE);      // Set DC Motor Direction

  // Optical Encoder
  encoderSetup();

  // Stepper Motor Control
  stepperBegin();
  stepperReset(STEPPER_RESET);

  // Limit Switches
  limitSwitchBegin();

  // WS2821b Pixel LED Control
  pixelBegin();
}
void loop() {
  //MOTOR TEST
  Serial.println("MOTOR TEST: (12s)");
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
  delay(2000);

//=================================================

  //OPTICAL ENCODER UNIT TEST
  Serial.println("ENCODER TEST: (7s)");
  for (int i = 0; i < 7000; i++)
  {
    encoderLoop(ENCODER_ACTIVE);
    delay(1);
  }
  encoderLoop(false);
  delay(2000);

//=================================================

  //STEPPER MOTOR UNIT TEST
  Serial.println("STEPPER TEST:");
  stepper_test(STEPPER_ACTIVE, NUM_REVOLUTIONS);
  delay(2000);

//=================================================

  //LED TEST
  Serial.println("LED TEST: (5s)");
  for (int i = 0; i < 100; i++)
  {
    pixelLoop(PIXEL_ACTIVE);
    delay(1);
  }
  pixelLoop(false);
  delay(2000);

//=================================================

  //LIMIT SWITCH TEST
  Serial.println("LIMIT SWITCH TEST: (10s)");
  for (int i = 0; i < 10000; i++)
  {
    limitSwitchLoop(LIMIT_SWITCH_ACTIVE);
    delay(1);
  }
  limitSwitchLoop(false);
  delay(2000);
}
