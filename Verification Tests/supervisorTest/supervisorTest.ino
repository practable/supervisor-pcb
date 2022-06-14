/* supervisor Test Firmware

    Imogen Wren
    25.05.2022

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


#define STUDENT_MOTOR_ENABLE      false                     // Software Tested
#define STUDENT_STEPPER_ENABLE    false                     // Software Tested
#define STUDENT_PIXEL_ENABLE      false                     // Software Tested

#define SHIFTREG_OVERWRITE        0b00000000                // Software Tested

#define DC_MOTOR_ENABLE           false                    // Software Tested
#define DC_MOTOR_CLOCKWISE        false                     // Tested but difficult to prove without actual hardware due to amount of hardware logic introduced
#define DC_MOTOR_SPEED            0                       // Software Tested
#define DC_CURRENT_SENSE_ACTIVE   false                    // Software Tested - Maths might not be correct but gives (some) usable(ish) data

#define ENCODER_ACTIVE            false                    // Tested Working but maths not accurate

#define STEPPER_ENABLE            true                      // !Needs Testing !      // Doesnt seem to do anything - because magic smoke released?  -- Have I got reset and EN the wrong way around?
#define STEPPER_CLOCKWISE         false                     // Software Tested
#define STEPPER_RESET             true                     // Software Tested    // Must be high to enable


#define STEPPER_ACTIVE            false                    // Half Tested - Needs Testing  // Pulse is stopped but motor still runs!? Doesnt if pulse pin tied top GND or Vcc - Because magic smoke Released?
#define STEPPER_DELAY_mS          500                       // Software Tested
#define STEPPER_FAULT_ACTIVE      false                     // Tested


#define SERVO_ACTIVE              false                     // Tested but no control

#define STUDENT_SERVO_DETECT      false                     // Needs Testing with 2nd MCU

#define PIXEL_ACTIVE              true                     // Software Tested

#define LIMIT_SWITCH_ACTIVE       false                    // Tested









void setup() {

  Serial.begin(115200);
  while ( !Serial ) delay(10);   // Might be required for Nano IoT 33

  // LED BUILTIN
  ledBegin();
 // flashBuiltIn(500, 10);

  // ShiftRegister and Enable Pins

  shiftReg.begin();   // Begin opens serial comms and sets shiftReg data pins to output
  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();   // Prints the current state of the shiftregister to serial monitor for debugging
  //  delay(1000);


  // The first way to use this API is to write functions for a specific device or channel we wish to enable or disable
  studentMotorEN(STUDENT_MOTOR_ENABLE);
  studentStepperEN(STUDENT_STEPPER_ENABLE);
  studentPixelEN(STUDENT_PIXEL_ENABLE);
  //  delay(3000);

  // The other way which might be more useful in testing is to just pass the output we want to overwriteState.
  // This will make setting up tests much easyer, as we can just specify the bitmask to pass to this function to set up the test correctly
  shiftReg.overwriteState(SHIFTREG_OVERWRITE);



  // DC Motor Control

  dcMotorBegin();              // Set control pins to output
  dcMotorEnable(DC_MOTOR_ENABLE );        // Need shift Register to enable board
  dcMotorDirection(DC_MOTOR_CLOCKWISE);      // Set DC Motor Direction
  dcMotorSpeed(DC_MOTOR_SPEED);             // Set DC Motor Speed   - default off
  // Still Need Current Sensing

  // Also Need Student Direction Detection


  // Optical Encoder
  encoderSetup();


  // Stepper Motor Control

  stepperBegin();
  stepperEnable(STEPPER_ENABLE);
  stepperDirection(STEPPER_CLOCKWISE);
  stepperReset(STEPPER_RESET);


  // Servo Motor Control
  servoBegin();                          // begin Servo functions
  servoConstrain(0, 130);             // Constrain min max travel for servo position



  // Limit Switches
  limitSwitchBegin();

  // WS2821b Pixel LED Control
  pixelBegin();
  // pixelChangePalette(hotpink_blue);


  // shiftReg.overwriteState(0b00000000);

}





void loop() {
  // Optical Encoder Loop
encoderLoop(ENCODER_ACTIVE);

  // Stepper loop test
  stepperPulse(STEPPER_ACTIVE, STEPPER_DELAY_mS);       // Move to loop to test

  stepperFaultDetect(STEPPER_FAULT_ACTIVE);

  // Servo Loop Test
  servoTest(SERVO_ACTIVE );                    // Must be run in loop updates the servo to the position passed - NOTE this will prove servo works, however there is no actual control there - it just moves backwards and forwards at random

  studentServoDetect(STUDENT_SERVO_DETECT);

  // Pixel Loop Test
  pixelLoop(PIXEL_ACTIVE );

  // Limit Switch Test
  limitSwitchLoop(LIMIT_SWITCH_ACTIVE);

  // DC Motor Current Sensing
  dcMotorCurrent(DC_CURRENT_SENSE_ACTIVE);
}
