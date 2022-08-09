#include "supervisor_pinMap.h"

#include "shiftRegister.h"

//Assigning names for the function of the pendulum board

#define STUDENT_LED1 DC_MOTOR_DIR1

#define STUDENT_LED2 DC_MOTOR_DIR2

#define STUDENT_LED3 SERVO_1

#define STUDENT_ENABLE STUDENT_M_EN

#define DRIVE DC_MOTOR_EN

#define LOAD STEPP_STEP



shiftRegister shiftReg(MOSI, SCK, LATCH);

void setup() {
  // put your setup code here, to run once:
  pinMode (STUDENT_LED1, OUTPUT);
  pinMode (STUDENT_LED2, OUTPUT);
  pinMode (STUDENT_LED3, OUTPUT);
  pinMode (STUDENT_ENABLE, OUTPUT);
  pinMode (DRIVE, OUTPUT);
  pinMode (LOAD, OUTPUT);
  shiftReg.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  shiftReg.shiftWrite(DRIVE, HIGH);
  
  digitalWrite (LOAD, LOW); //load
 
  shiftReg.shiftWrite(STUDENT_ENABLE, LOW);
 
  digitalWrite(STUDENT_LED1, HIGH); //RED LED

  digitalWrite(STUDENT_LED2, HIGH); //ORANGE LED

  digitalWrite(STUDENT_LED3, HIGH); //GREEN LED


}
