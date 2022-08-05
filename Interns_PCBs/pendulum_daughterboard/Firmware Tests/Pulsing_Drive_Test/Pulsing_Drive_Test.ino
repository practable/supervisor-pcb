#include "supervisor_pinMap.h"

#include "shiftRegister.h"

#include <autoDelay.h>

#include "basicFunctions.h"       // Basic functions like pin reads that didnt need an entire page

//#include "shiftFunctions.h"       // Shiftregister functions (defined outside the library and specific to this project)

#include "encoderFunctions.h"     // Optical Encoder functions

#include "opticalEncoder.h"     //Optical Encoder Values

//#include "opticalEncoder.cpp"     //Optical Encoder Values




/* Test Settings

    Enable and disables various functions to test hardware function by function


*/


#define STUDENT_MOTOR_ENABLE      false                     // Software Tested
#define STUDENT_STEPPER_ENABLE    false                     // Software Tested
#define STUDENT_PIXEL_ENABLE      false                     // Software Tested

#define SHIFTREG_OVERWRITE        0b00000000                // Software Tested

#define DC_MOTOR_ENABLE           false                    // Software Tested
#define DC_MOTOR_CLOCKWISE        false                     // Tested but difficult to prove without actual hardware due to amount of hardware logic introduced
#define DC_MOTOR_SPEED            0                      // Software Tested
#define DC_CURRENT_SENSE_ACTIVE   false                    // Software Tested - Maths might not be correct but gives (some) usable(ish) data

#define ENCODER_ACTIVE            true                    // Tested Working but maths not accurate

#define STEPPER_ENABLE            false                      // Enable pin now controlled from stepper function not independently
#define STEPPER_CLOCKWISE         false                     // Stepper direction now controlled from stepper function not independently
#define STEPPER_RESET             false                     // Software Tested // Must be hight to enable  


#define STEPPER_ACTIVE            false                    // Software TEsted
#define NUM_REVOLUTIONS           2
#define STEPPER_FAULT_ACTIVE      false                     // Tested


#define SERVO_ACTIVE              false                     // Tested

#define STUDENT_SERVO_DETECT      false                     // Needs Testing with 2nd MCU

#define PIXEL_ACTIVE              false                     // Software Tested

#define LIMIT_SWITCH_ACTIVE       false                    // Tested

//Assigning names for the function of the pendulum board

#define STUDENT_LED1 DC_MOTOR_DIR1

#define STUDENT_LED2 DC_MOTOR_DIR2

#define STUDENT_LED3 SERVO_1

#define STUDENT_ENABLE STUDENT_M_EN

#define DRIVE DC_MOTOR_EN

#define LOAD STEPP_STEP



shiftRegister shiftReg(MOSI, SCK, LATCH);

bool direction;
bool clockwiseRotation;
int32_t heading_milliDeg;

void setup() {
  

  Serial.begin(115200);
  while ( !Serial ) delay(10);   // Might be required for Nano IoT 33

  // Defining pins for the Pendulum PCB
  
  pinMode (STUDENT_LED1, OUTPUT);
  pinMode (STUDENT_LED2, OUTPUT);
  pinMode (STUDENT_LED3, OUTPUT);
  pinMode (STUDENT_ENABLE, OUTPUT);
  pinMode (DRIVE, OUTPUT);
  pinMode (LOAD, OUTPUT);
  shiftReg.begin();

  // Optical Encoder
  encoderSetup();
}

void loop() {
  
  // Optical Encoder Loop

  encoderLoop(ENCODER_ACTIVE);
  shiftReg.shiftWrite(STUDENT_ENABLE, LOW);

  digitalWrite (LOAD, LOW); //load
  digitalWrite(STUDENT_LED1, HIGH); //RED LED
  digitalWrite(STUDENT_LED2, LOW); //ORANGE LED
  digitalWrite(STUDENT_LED3, LOW); //GREEN LED 

  delay(100);

  if (clockwiseRotation == true && 1000 <= heading_milliDeg <= 1100)
  {
    shiftReg.shiftWrite(DRIVE, HIGH);  
    digitalWrite (LOAD, LOW); //load
    digitalWrite(STUDENT_LED1, HIGH); //RED LED
    digitalWrite(STUDENT_LED2, LOW); //ORANGE LED
    digitalWrite(STUDENT_LED3, LOW); //GREEN LED
  }
  else if (clockwiseRotation == false && 1000 >= heading_milliDeg >= 900)
  {
    shiftReg.shiftWrite(DRIVE, HIGH);  
    digitalWrite (LOAD, LOW); //load
    digitalWrite(STUDENT_LED1, LOW); //RED LED
    digitalWrite(STUDENT_LED2, HIGH); //ORANGE LED
    digitalWrite(STUDENT_LED3, LOW); //GREEN LED
  }
  else 
  {
    shiftReg.shiftWrite(DRIVE, HIGH);  
    digitalWrite (LOAD, LOW); //load
    digitalWrite(STUDENT_LED1, LOW); //RED LED
    digitalWrite(STUDENT_LED2, LOW); //ORANGE LED
    digitalWrite(STUDENT_LED3, HIGH); //GREEN LED
  }
  


}
