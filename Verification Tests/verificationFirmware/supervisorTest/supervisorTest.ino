/* supervisor Test Firmware

    Imogen Wren
    25.05.2022

  Test firmware contains libraries suitable for testing all hardware





*/


#include "supervisor_pinMap.h"    // PinMap for Supervisor pcb - Supervisor MCU

#include "shiftRegister.h"        // shiftRegister Library

#include "shiftFunctions.h"       // Shiftregister functions (defined outside the library and specific to this project)

#include "dcMotorFunctions.h"     // DC Motor Functions

#include "stepperFunctions.h"     // Stepper Motor Functions


shiftRegister shiftReg(MOSI, SCK, LATCH);



void setup() {

  // LED BUILTIN

  // ShiftRegister and Enable Pins
  shiftReg.begin();   // Begin opens serial comms and sets shiftReg data pins to output
  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();   // Prints the current state of the shiftregister to serial monitor for debugging
  delay(1000);


  // The first way to use this API is to write functions for a specific device or channel we wish to enable or disable
  studentMotorEN(false);
  studentStepperEN(false);
  studentPixelEN(false);
  delay(3000);

  // The other way which might be more useful in testing is to just pass the output we want to overwriteState.
  // This will make setting up tests much easyer, as we can just specify the bitmask to pass to this function to set up the test correctly
  shiftReg.overwriteState(0b00001000);



  // DC Motor Control
  dcMotorBegin();              // Set control pins to output
  dcMotorEnable(false);        // Need shift Register to enable board
  dcMotorDirection(true);      // Set DC Motor Direction
  dcMotorSpeed(0);             // Set DC Motor Speed   - default off
  // Still Need Current Sensing

  // Stepper Motor Control
  stepperBegin();
  stepperEnable(false);
  stepperDirection(false);
  stepperReset(false);
  stepperPulse(false, 500);
  // Still Need Fault Detection
  stepperFaultDetect();

  // Servo Motor Control
  

  // Limit Switches

  // WS2821b Pixel LED Control

  
}






void loop() {


}
