#include "supervisor_pinMap.h"

#include "shiftFunctions.h"  

void setup() {
  // put your setup code here, to run once:
//  pinMode (STU_LED_1, OUTPUT);
//  pinMode (STU_LED_2, OUTPUT);
//  pinMode (STU_LED_3, OUTPUT);
  pinMode (DC_MOTOR_DIR1, OUTPUT);
  pinMode (DC_MOTOR_DIR2, OUTPUT);
  pinMode (SERVO_1, OUTPUT);
  pinMode (STUDENT_M_EN, OUTPUT);
  pinMode (DC_MOTOR_EN, OUTPUT);
  pinMode (STEPP_STEP, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

 digitalWrite (DC_MOTOR_EN, LOW); //drive
 digitalWrite (STEPP_STEP, LOW); //load

 if (digitalRead(DC_MOTOR_EN) == LOW  && digitalRead(STEPP_STEP) == LOW)
  {
    digitalWrite(DC_MOTOR_DIR1, HIGH);
  }

  if ( digitalRead(DC_MOTOR_EN) == HIGH  && digitalRead(STEPP_STEP) == LOW)
  {
    digitalWrite(DC_MOTOR_DIR2, HIGH);
  }

  if (digitalRead(DC_MOTOR_EN) == LOW  && digitalRead(STEPP_STEP) == HIGH)
  {
    digitalWrite(SERVO_1, HIGH);
  }

  
  if (digitalRead(DC_MOTOR_EN) == HIGH  && digitalRead(STEPP_STEP) == HIGH)
  {
    digitalWrite(SERVO_1, HIGH);
    digitalWrite(DC_MOTOR_DIR1, HIGH);
    digitalWrite(DC_MOTOR_DIR2, HIGH);
  }

}
