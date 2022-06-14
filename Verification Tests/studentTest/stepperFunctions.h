/* stepperFunctions.h

    Just a place to store Stepper Motor Functions

    Stepper Motor Pins:

    Control:
    #define STEPP_DIR            Q4
    #define STEPP_EN             Q5        // Must be LOW to enable
    #define STEPP_RST            Q6        // Must be HIGH to enable

    #define STEPP_STEP          6

    Sense/Fault Detect:

    #define STEPP_FLT           19    (A4)


*/

#ifndef stepperFunctions_h
#define stepperFunctions_h


//#include "supervisor_pinMap.h"

#include <autoDelay.h>

autoDelay stepPulse;

bool stepPulseState;

void stepperBegin() {
  pinMode(STEPP_STEP, OUTPUT);
  pinMode(STEPP_FLT, INPUT);
}

void stepperEnable(bool enable) {
  if (enable) {
    shiftReg.shiftWrite(STEPP_EN, HIGH);
  }
  shiftReg.shiftWrite(STEPP_EN, LOW);
}

void stepperDirection(bool clockwise = false) {
  shiftReg.shiftWrite(STEPP_DIR, clockwise);
}

void stepperReset(bool reset = false) {
  shiftReg.shiftWrite(STEPP_RST, reset);
}

void stepperPulse(bool runMotor = false, uint32_t pulseDelay_mS = 500) {   // Trying out Guard Clauses Technique instead of nested if statements - Didnt work will test on something less important later
  if (runMotor) {
    if (stepPulse.millisDelay(pulseDelay_mS)) {
      if (stepPulseState) {
        stepPulseState = LOW;
      } else {
        stepPulseState = HIGH;
      }
      Serial.println("Pulse");
      digitalWrite(STEPP_STEP, stepPulseState);
    }
  } else {
    if (stepPulseState) {
      stepPulseState = LOW;
      digitalWrite(STEPP_STEP, stepPulseState);
    }
  }
}




void stepperFaultDetect(bool active) {
  if (active) {
    int16_t stepperFault = digitalRead(STEPP_FLT);
    if (stepperFault) {
      //  Serial.println("Stepper Operation Nominal");
    } else {
      Serial.println("Stepper Fault Detected");
    }
  }
}







void stepper_test(bool active, uint16_t num_revolutions = 1) {
  if (active) {
    // Set the spinning direction clockwise:
    shiftReg.shiftWrite(STEPP_DIR , HIGH);
    stepperEnable (true);                          // Enable the driver (Leaving enabled causes motor overheating)

    // Spin the stepper motor n revolutions fast:
    for (int i = 0; i < 6400 * num_revolutions; i++) {
      // These four lines result in 1 step:
      digitalWrite(STEPP_STEP, HIGH);
      delayMicroseconds(500);
      digitalWrite(STEPP_STEP, LOW);
      delayMicroseconds(500);
      Serial.println("CW");
    }
    stepperEnable (false);                          // disable the driver (Leaving enabled causes motor overheating)
    delay(1000);

    // Set the spinning direction counterclockwise:
    shiftReg.shiftWrite(STEPP_DIR , LOW);
    stepperEnable (true);                          // Enable the driver (Leaving enabled causes motor overheating)
    //Spin the stepper motor 5 revolutions fast:
    for (int i = 0; i < 6400 * no_of_revolutions; i++) {
      // These four lines result in 1 step:
      digitalWrite(STEPP_STEP, HIGH);
      delayMicroseconds(500);
      digitalWrite(STEPP_STEP, LOW);
      delayMicroseconds(500);
      Serial.println("ACW");
    }
    stepperEnable (false);
    delay(1000);
  }
}




#endif
