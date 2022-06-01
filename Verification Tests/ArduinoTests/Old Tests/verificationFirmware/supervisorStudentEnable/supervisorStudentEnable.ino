/* shiftRegister API Test

    Imogen Wren
    25.05.2022

   shiftRegister pins are defined using Q0 - Q7 notation. This avoids pin definition conflicts with arduino pins, regardless of the platform used.



   Supervisor PCB Pindeclarations
  #define DC_MOTOR_EN          Q0
  #define STUDENT_M_EN         Q1
  #define STUDENT_STEP_EN      Q2
  #define STUDENT_PIXEL_EN     Q3
  #define STEPP_DIR            Q4
  #define STEPP_EN             Q5
  #define STEPP_RST            Q6
  #define SHIFT_REG_7          Q7



     For this test software, we simply wish to be able to enable and disable outputs from the supervisor MCU

*/


#include "supervisor_pinMap.h"

#include "shiftRegister.h"




shiftRegister shiftReg(MOSI, SCK, LATCH);



void setup() {
  shiftReg.begin();   // Begin opens serial comms and sets shiftReg data pins to output


  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();
  delay(1000);


  // The first way to use this API is to write functions for a specific device or channel we wish to enable or disable
  dcMotorEnable(true);
  shiftReg.printState();

  studentMotorEN(true);
  shiftReg.printState();

  studentStepperEN(true);
  shiftReg.printState();

  studentPixelEN(true);
  shiftReg.printState();

  delay(3000);
  
  shiftReg.allOff();  // Turn off all the shiftReg pins
  shiftReg.printState();
  delay(2000);

  // The other way which might be more useful in testing is to just pass the output we want to overwriteState.
  // This will make setting up tests much easyer, as we can just specify the bitmask to pass to this function to set up the test correctly
  shiftReg.overwriteState(0b00001000);

  shiftReg.printState();

}




void loop() {


}


// Motor Driver Enable - Must be high to run motor

void dcMotorEnable(bool state) {
  shiftReg.shiftWrite(DC_MOTOR_EN, state);
}



// Motor Driver Control


// Student Control Enables & Disables
void studentMotorEN(bool state) {
  shiftReg.shiftWrite(STUDENT_M_EN, state);
}



void studentStepperEN(bool state) {
  shiftReg.shiftWrite(STUDENT_STEP_EN, state);
}



void studentPixelEN(bool state) {
  shiftReg.shiftWrite(STUDENT_PIXEL_EN, state);
}
