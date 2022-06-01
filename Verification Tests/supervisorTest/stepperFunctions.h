/* stepperFunctions.h

    Just a place to store Stepper Motor Functions

    Stepper Motor Pins:

    Control:
    #define STEPP_DIR            Q4
    #define STEPP_EN             Q5
    #define STEPP_RST            Q6

    #define STEPP_STEP          6

    Sense/Fault Detect:

    #define STEPP_FLT           19


*/

#ifndef stepperFunctions_h
#define stepperFunctions_h

//#include "supervisor_pinMap.h"

#include <autoDelay.h>

autoDelay stepPulse;

bool stepPulseState;

void stepperBegin() {
  pinMode(STEPP_STEP, OUTPUT);
}

void stepperEnable(bool enable) {
  shiftReg.shiftWrite(STEPP_EN, enable);
}

void stepperDirection(bool clockwise = false) {
  shiftReg.shiftWrite(STEPP_DIR, clockwise);
}

void stepperReset(bool reset = false) {
  shiftReg.shiftWrite(STEPP_DIR, reset);
}

void stepperPulse(bool runMotor = false, uint32_t pulseDelay_mS = 500) {   // Trying out Guard Clauses Technique instead of nested if statements
  if (!runMotor) {
    return;
  }
  if (!stepPulse.millisDelay(pulseDelay_mS)) {
    return;
  }
  if (stepPulseState) {
    stepPulseState = LOW;
  } else {
    stepPulseState = HIGH;
  }
  digitalWrite(STEPP_STEP, stepPulseState);
}




void stepperFaultDetect() {
  bool stepperFault = digitalRead(STEPP_FLT);
  if (stepperFault) {
    Serial.println("Stepper Fault Detected");
  } else {
    //  Serial.println("Stepper Operation Nominal");
  }
}


#endif
