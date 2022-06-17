/* Basic functions for testing

   Mostly just to tie basic inputs and outputs to named functions for neatness


   #define LED_BUILTIN         D13


   #define LIMIT_1             18

*/


#ifndef basicFunctions_h
#define basicFunctions_h



void ledBegin() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void flashBuiltIn(uint32_t delayTime = 1000, byte noLoops = 6) {
  while (noLoops > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delayTime);
    digitalWrite(LED_BUILTIN, LOW);
    noLoops--;
  }
}


void limitSwitchBegin() {
  pinMode(LIMIT_1, INPUT);
}


bool limitSwitchPressed;   // latching bool might be used later to cycle through test options

void limitSwitchLoop(bool active = false) {
  if (active) {
    int16_t limitSwitchState = digitalRead(LIMIT_1);
    if (limitSwitchState == HIGH) {
      limitSwitchPressed = true;
      Serial.println("Limit Switch Pressed");
    }
  }
}




#endif
