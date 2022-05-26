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

void stepperPulse(bool runMotor = false, uint32_t pulseDelay_mS = 500) {
  if (runMotor) {
    digitalWrite(STEPP_STEP, HIGH);
    delay(pulseDelay_mS);
    digitalWrite(STEPP_STEP, LOW);
    delay(pulseDelay_mS)
  }
}


void stepperFaultDetect(){
  stepperFault = digitalRead(STEPP_FAULT);
  if (stepperFault){
    Serial.println("Stepper Fault Detected");
  } else {
    Serial.println("Stepper Operation Nominal");
  }
}


#endif
