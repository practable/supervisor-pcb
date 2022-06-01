/* supervisor Test Firmware

    Imogen Wren
    25.05.2022

  Test firmware contains libraries suitable for testing all hardware





*/


#include "supervisor_pinMap.h"    // PinMap for Supervisor pcb - Supervisor MCU

#include "ledFunctions.h"          // Built in LED Flash

#include "shiftFunctions.h"       // Shiftregister functions (defined outside the library and specific to this project)

#include "dcMotorFunctions.h"     // DC Motor Functions

#include "encoderFunctions.h"     // Optical Encoder functions

#include "stepperFunctions.h"     // Stepper Motor Functions

#include "servoFunctions.h"       // Servo Motor Functions

#include "pixelFunctions.h"        // WS2821b LED functions






void setup() {

  // LED BUILTIN
  ledBegin();
  flashBuiltIn(200, 10);

  // ShiftRegister and Enable Pins

  shiftReg.begin();   // Begin opens serial comms and sets shiftReg data pins to output
  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();   // Prints the current state of the shiftregister to serial monitor for debugging
//  delay(1000);


  // The first way to use this API is to write functions for a specific device or channel we wish to enable or disable
  studentMotorEN(false);
  studentStepperEN(false);
  studentPixelEN(false);
//  delay(3000);

  // The other way which might be more useful in testing is to just pass the output we want to overwriteState.
  // This will make setting up tests much easyer, as we can just specify the bitmask to pass to this function to set up the test correctly
  shiftReg.overwriteState(0b00000000);



  // DC Motor Control
  /*
    dcMotorBegin();              // Set control pins to output
    dcMotorEnable(false);        // Need shift Register to enable board
    dcMotorDirection(false);      // Set DC Motor Direction
    dcMotorSpeed(0);             // Set DC Motor Speed   - default off
    // Still Need Current Sensing

    // Also Need Student Direction Detection
  */



  // Stepper Motor Control

  stepperBegin();
  stepperEnable(false);
  stepperDirection(false);
  stepperReset(false);

  // Still Need Fault Detection
  stepperFaultDetect();


  // Servo Motor Control
  servoBegin();                          // begin Servo functions
  servoConstrain(-180, 180);             // Constrain min max travel for servo position



  // Limit Switches

  // WS2821b Pixel LED Control
  pixelBegin();
 // pixelChangePalette(hotpink_blue);


}






void loop() {

  // Stepper loop test
  stepperPulse(false, 500);       // Move to loop to test

  // Servo Loop Test
  servoTest(false);                    // Must be run in loop updates the servo to the position passed - NOTE this will prove servo works, however there is no actual control there - it just moves backwards and forwards at random

  // Pixel Loop Test
  pixelLoop(true);
}
