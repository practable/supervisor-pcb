/* dcMotorFunctions.h
 * 
 *  Just a place to store dcMotor Functions
 *  
 *  DC Motor Pins
 *  Outputs
 *  #define DC_MOTOR_PWM        10
 *  #define DC_MOTOR_DIR1       12
 *  #define DC_MOTOR_DIR2       7
 *  
 *  Enable
 *  #define DC_MOTOR_EN          Q0
 *  
 *  Sense Pins
 *  #define DC_MOTOR_IS2        A6
 *  #define DC_MOTOR_IS1        A7
 *  
 *  
 * 
 */


#ifndef dcMotorFunctions_h
#define dcMotorFunctions_h



 
// DC Motor Driver Board control
void dcMotorBegin() {
  pinMode(DC_MOTOR_PWM, OUTPUT);
  pinMode(DC_MOTOR_DIR1, OUTPUT);
  pinMode(DC_MOTOR_DIR2, OUTPUT);
}





// Enable must be high to actuate motor  (Needs shift register library to access)
void dcMotorEnable(bool state) {
  shiftReg.shiftWrite(DC_MOTOR_EN, state);
}





// Direction Control DC Motor
/*
  // Notes on H-Bridge Drivers https://www.modularcircuits.com/blog/articles/h-bridge-secrets/h-bridges-the-basics/
  // Additional Information on dead time insertion https://hackaday.io/project/3176-gator-quad/log/11741-pwm-control-and-dead-time-insertion

  As I am lazy I am just going to use the value at the end of the hackaday article as a baseline deadtime 1.5x10^-7 seconds which is microseconds,
  so a delay time of just a few milliseconds should be sufficient to avoid shootthrough
*/

#define DEADTIME_MS 10
void dcMotorDirection(bool clockwise = true) {
  digitalWrite(DC_MOTOR_DIR1, LOW);
  digitalWrite(DC_MOTOR_DIR2, LOW);
  delay(DEADTIME_MS);
  if (clockwise) {
    digitalWrite(DC_MOTOR_DIR1, HIGH);
  } else {
    digitalWrite(DC_MOTOR_DIR2, HIGH);
  }
}





// Change motor drive level.
// Further reading on PWM Output incase we need to change PWM frequency https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
#define MAX_MOTOR_SPEED 255                                  // Set a max drive level to constrain motor speed
void dcMotorSpeed(uint16_t pwmOut = 0) {
  pwmOut = constrain(pwmOut, 0, MAX_MOTOR_SPEED);
  analogWrite(DC_MOTOR_PWM, pwmOut);
}


// DONT FORGET ABOUT CURRENT SENSING





#endif
