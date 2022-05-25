/* shiftRegister API Test
 *  
 *  Imogen Wren
 *  25.05.2022
 * 
 * shiftRegister pins are defined using Q0 - Q7 notation. This avoids pin definition conflicts with arduino pins, regardless of the platform used.
 * 
 *
 *
 * Supervisor PCB Pindeclarations
#define DC_MOTOR_EN          Q0
#define STUDENT_M_EN         Q1
#define STUDENT_STEP_EN      Q2
#define STUDENT_PIXEL_EN     Q3
#define STEPP_DIR            Q4
#define STEPP_EN             Q5
#define STEPP_RST            Q6
#define SHIFT_REG_7          Q7
 * 
 * 
 *   
 *   For this test software, we simply wish to be able to enable and disable outputs from the supervisor MCU
 * 
 */

#include "shiftRegister.h"

#include "supervisor_pinMap.h"


shiftRegister shiftReg(MISO, SCK, LATCH);



void setup() {
shiftReg.begin();
dcMotorEnable(true);

studentMotorEN(false);
studentStepperEN(false);
studentPixelEN(false);


}




void loop() {

}


// Motor Driver Enable - Must be high to run motor 

void dcMotorEnable(bool state){
shiftReg.shiftWrite(DC_MOTOR_EN, state);  
}



// Motor Driver Control


// Student Control Enables & Disables
void studentMotorEN(bool state){
  shiftReg.shiftWrite(STUDENT_M_EN, state);
}



void studentStepperEN(bool state){
  shiftReg.shiftWrite(STUDENT_STEPP_EN, state);
}



void studentPixelEN(bool state){
  shiftReg.shiftWrite(STUDENT_PIXEL_EN, state);
}
