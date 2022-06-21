/*   Pin Testing Sketch

      Trying to identify issues with arduino framework for digitalRead() on ADC enabled pins while performing analogRead() simaltaniously

      BM & IH


      Test performed by placing 1k resistors between test pins and bus wire. Bus wire is pulled to Vcc or GND and pin values compared to expected values.

      Test Results:
      - No Issues found when performing digitalRead and analogRead on different pins
      - digital value returned by digitalRead is 0 when an analogRead is performed on the same pin regardless of pin state

      Conclusions:
      Although effort was taken to avoid Our origional software may have inadvertantly set pins incorrectly. Simplifed test software generated to test each function independently.

*/


// Settings

int dInPins[]     = {8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5, A6, A7 };          //List of all Arduino pins to be tested as digital inputs
int aInPins[]     = {A2, A3};                                                         // List of all Arduino pins to be tested as analog inputs
int dOutPins[]    = {4 , 7};                                                          // List of all Arduino pins to be set as Digital Outputs
int pwmOutPins[]  = {2, 3, 5};                                                     // List of all Arduino pins to be set as PWM Outputs


#define D_OUT_STATE HIGH                         // Set all digital outputs to this value
#define PWM_OUT_VAL 100                           // Set all PWM Outputs to this value                 


#define SAMPLE_RATE_HZ 100                        // Sample rate for reading pins and printing values to serial monitor


//Global Variables

int dInPinCount;                                                                 //Number of Pins
int aInPinCount;                                                                 //Number of Pins
int dOutPinCount;
int pwmOutPinCount;

uint32_t sampleDelay_mS = 500;



void setup() {

  // Setup Serial and wait for comms
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  // Print heading and calculate number of pins in each category
  Serial.println("Arduino Nano IoT 33 Pin Test");
  dInPinCount = sizeof(dInPins) / 4;
  Serial.print("Num Digital Input Pins: ");
  Serial.println(dInPinCount);
  aInPinCount = sizeof(aInPins) / 4;
  Serial.print("Num Analog Input Pins: ");
  Serial.println(aInPinCount);
  dOutPinCount = sizeof(dOutPins) / 4;
  Serial.print("Num Digital Input Pins: ");
  Serial.println(dOutPinCount);
  pwmOutPinCount = sizeof(pwmOutPins) / 4;
  Serial.print("Num Analog Input Pins: ");
  Serial.println(pwmOutPinCount);

  delay(2000);

  // Calculate the delay required to meet the sample rate defined
  sampleDelay_mS = 1000 / SAMPLE_RATE_HZ;


  // Loops to set all pins to correct mode
  for (int i = 0; i < dInPinCount; i++) {
    pinMode(dInPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < dOutPinCount; i++) {
    pinMode(dOutPins[i], OUTPUT);
  }
  for (int i = 0; i < pwmOutPinCount; i++) {
    pinMode(pwmOutPins[i], OUTPUT);
  }

  // Set all output pins to the value required for test
  for (int i = 0; i < dOutPinCount; i++) {
    digitalWrite(dOutPins[i], D_OUT_STATE);
  }

  for (int i = 0; i < pwmOutPinCount; i++) {
    analogWrite(pwmOutPins[i], PWM_OUT_VAL);
  }
}


uint32_t lastSampleTime;

void loop() {
  if (millis() - lastSampleTime >= sampleDelay_mS) {
    lastSampleTime = millis();
    //For Loop to Read Values on the Pins
    int dValList[dInPinCount];                              //Create empty list of read values
    for (int i = 0; i < dInPinCount; i++) {
      dValList[i] = digitalRead(dInPins[i]);
    }

    int aValList[aInPinCount];
    for (int i = 0; i < aInPinCount; i++) {
      aValList[i] = analogRead(aInPins[i]);
    }

    //Loop to Print the Values
    for (int i = 0; i < dInPinCount; i++) {
      Serial.print(dValList[i]);
      Serial.print(",  ");
    }
    Serial.print("   ");
    for (int i = 0; i < aInPinCount; i++) {
      Serial.print(aValList[i]);
      Serial.print(",  ");
    }
    Serial.println(" ");
  }
}






//Old Function defined to manually convert Analog Values to Digital. NOT USED ANYMORE.
int analogToDigital(int pin) {
  if (analogRead(pin) < 512)
    return 0;
  else
    return 1;
}
