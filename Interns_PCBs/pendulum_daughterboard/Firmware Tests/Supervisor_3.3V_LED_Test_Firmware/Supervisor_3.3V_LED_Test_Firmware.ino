#include "supervisor_pinMap.h"

#include "shiftRegister.h"

//Assigning names for the function of the pendulum board

#define SUP_LED_1 DC_MOTOR_DIR1

#define SUP_LED_2 DC_MOTOR_DIR2

#define SUP_LED_3 SERVO_1

#define STU_ENABLE STUDENT_M_EN

#define DRIVE DC_MOTOR_EN

#define LOAD STEPP_STEP

shiftRegister shiftReg(MOSI, SCK, LATCH);



void setup() {
  // put your setup code here, to run once:

  pinMode (SUP_LED_1, OUTPUT);
  pinMode (SUP_LED_2, OUTPUT);
  pinMode (SUP_LED_3, OUTPUT);
  pinMode (STU_ENABLE, OUTPUT);
  pinMode (DRIVE, OUTPUT);
  pinMode (LOAD, OUTPUT);
  shiftReg.begin();


//flashLED();
}



void loop() {
//Initially setting all the pins low


 shiftReg.shiftWrite(DRIVE, LOW);  
 digitalWrite (LOAD, LOW); 
 shiftReg.shiftWrite(STU_ENABLE, LOW);
 digitalWrite (SUP_LED_1, HIGH);
 digitalWrite (SUP_LED_2, HIGH);
 digitalWrite (SUP_LED_3, HIGH);

  // Trying to turn the pins on without enable

  //delay(3000);
//  digitalWrite (STU_LED_1, HIGH);
 // delay(1000);
  //digitalWrite (STU_LED_1,  LOW);
  //digitalWrite (STU_LED_2, HIGH);
 // delay(1000);
  //digitalWrite (STU_LED_2, LOW);
  //digitalWrite (STU_LED_3, HIGH);
  //delay(1000);
  //digitalWrite (STU_LED_3, LOW);
  //digitalWrite (SUP_LED_1, HIGH);
  //delay(1000);
  //digitalWrite (SUP_LED_1, LOW);
  //digitalWrite (SUP_LED_2, HIGH);
 // delay(1000);
  //digitalWrite (SUP_LED_2, LOW);
 // digitalWrite (SUP_LED_3, HIGH);

  // Trying to turn the pins on with enable
 // delay(1000);
 // digitalWrite (STU_ENABLE, HIGH);
 // delay(1000);
 // digitalWrite (SUP_LED_3, LOW);
//  digitalWrite (STU_LED_1, HIGH);
 // delay(1000);
//  digitalWrite (STU_LED_1,  LOW);
//  digitalWrite (STU_LED_2, HIGH);
//  delay(1000);
 // digitalWrite (STU_LED_2, LOW);
 // digitalWrite (STU_LED_3, HIGH);
 // delay(1000);
 // digitalWrite (STU_LED_3, LOW);
 // digitalWrite (SUP_LED_1, HIGH);
 // delay(1000);
 // digitalWrite (SUP_LED_1, LOW);
 // digitalWrite (SUP_LED_2, HIGH);
 // delay(1000);
 // digitalWrite (SUP_LED_2, LOW);
  //digitalWrite (SUP_LED_3, HIGH);



}


void flashLED() {
  int count = 6;
  while (count) {
    digitalWrite (SUP_LED_1, HIGH);
    delay(500);
    digitalWrite (SUP_LED_1,  LOW);
    delay(200);
    count--;
  }
}
