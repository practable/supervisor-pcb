/* INPUT_CHECK

    Directly print the status of the input pins for debugging hardware

*/

#define INDEX_PIN 4    //Not sure what this pin is actually required for
#define PIN_A     2
#define PIN_B     3

#include <autoDelay.h>

void setup() {
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // Might be required for Nano IoT 33
  Serial.println("TESTING");
  encoderBegin();
}

void loop() {
  testInputs();
}


void encoderBegin() {
  pinMode (INDEX_PIN, INPUT);
  pinMode (PIN_A, INPUT);
  pinMode (PIN_B, INPUT);
  //  __enable_irq();                 // Enable global interrupts?
}

void testPlot(int A, int B, int C) {
  char buffer[64];
  sprintf(buffer, "%i, %i, %i ", A, B, C);
  Serial.println(buffer);
}


autoDelay printDelay;
#define PRINT_DELAY 10

void testInputs() {
  if (printDelay.millisDelay(PRINT_DELAY)) {
    int pinAstate = digitalRead(PIN_A);
    int pinBstate = digitalRead(PIN_B);
    int indexState = digitalRead(INDEX_PIN);
    testPlot(pinAstate, pinBstate, indexState);
  }
  //testPlot(pinAstate, 0, 0);
}
