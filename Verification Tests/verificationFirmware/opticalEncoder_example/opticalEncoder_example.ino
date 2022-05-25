/*   opticalEncoder Example

      Test Program for Broadcom Incremental Encoder 500 ppr, AEDB-9140-A13 optical encoder

      Optical Encoder:
      https://uk.rs-online.com/web/p/motion-control-sensors/7967806

      Datasheet:
      https://docs.rs-online.com/34ce/0900766b812cdcb0.pdf



     Test software aims to count "Ticks" and Direction to prove hardware is functional.

     Can be expanded to return RPM of motor, and possibly absolute position in (degrees) given a calibration for starting position.

      Imogen Heard 25/04/2022

      Test for Supervisor PCB for practicable.io remote Lab Experiments


*/

/*  Encoder Specifics:

     1000 ppt encoder

     Therefore rotaryCount will be init at 1000, and its range constrained to 1000 +- 500
     to track absolute position



*/

#include <autoDelay.h>

#define INDEX_PIN 4    //Not sure what this pin is actually required for
#define PIN_A     2
#define PIN_B     3


// Global Variables

bool up;
bool fired;

bool direction;

bool clockwiseRotation;


uint16_t rotaryCount = 1000;
uint16_t prevCount;

float heading_deg;
char headingString[32];    // Global buffer just for saving float values into a string for easy printing


int rpm;

void setup() {
  Serial.begin(115200);
  attachInterrupt (digitalPinToInterrupt (PIN_A), isr , CHANGE);   // interrupt 0 is pin 2
  encoderBegin();
  plotHeader();

}




void loop() {
  encoderDirection();
  calcHeading(rotaryCount);
  calcRPM();

  plotEncoder();

  // testInputs();
}





void testPlot(int A, int B, int C) {
  char buffer[64];
  sprintf(buffer, "%i, %i, %i ", A, B, C);
  Serial.println(buffer);
}

void plotHeader() {
  Serial.println("Ticks, Heading");
}

void encoderBegin() {
  pinMode (INDEX_PIN, INPUT);
  pinMode (PIN_A, INPUT);
  pinMode (PIN_B, INPUT);
}

void testInputs() {
  int pinAstate = digitalRead(PIN_A);
  int pinBstate = digitalRead(PIN_B);
  int indexState = digitalRead(INDEX_PIN);
  testPlot(pinAstate, pinBstate, indexState);
  //testPlot(pinAstate, 0, 0);
}


// Function to calculate the velocity of the rotaryEncoder in rpm
int16_t previousAngle;

uint32_t sampleDelay_uS = 100;

autoDelay sampleDelay;


// This does not work, probably a sample time issue There will be a way around it but I dont have the time to explore now. 
void calcRPM() {
  if (sampleDelay.microsDelay(sampleDelay_uS)) {
    int currentAngle = rotaryCount;
    int difference_uS = previousAngle - currentAngle ;
    // We now have the distance moved in deg over time sampleDelay_mS
    // Multiply this to seconds
    int difference_S = difference_uS * (1000000 / sampleDelay_uS);

    // Multiply this difference average over a second to 1 minuite
    int difference_m = (difference_S * 60);

    // divide the difference in ticks by 1000 as 1000 makes a complete revolution

    rpm = difference_m / 1000;
    previousAngle = currentAngle;
  }
}





// Function to return the current position of the encoder in degrees from center position (1000)  (-180 to +180)deg

// 180/500 = 0.36 so each pulse is 0.36deg apart - makes sense 360/1000ppt should have seen that coming

float calcHeading(int16_t encoderPos) {
  heading_deg = (encoderPos - 1000) * 0.36;
  // Serial.println(heading_deg);
  floatToChar(heading_deg);    // THis returns a global variaable for now for ease
  return heading_deg;
}


// Also saving some data as a char string to use later
void floatToChar (float finput) {
  // char *tmpSign = (finput < 0) ? "-" : "";         // Work out what sign to add
  float tmpVal = (finput < 0) ? finput * -1 : finput; // If less than 0, make positive

  int tmpInt1 = int(finput);   // cast to int to get before .point
  float tmpFrac = tmpVal - tmpInt1;  // Get the fraction
  int tmpInt2 = trunc(tmpFrac * 1000);   // Turn into an integer

  tmpInt2 = (tmpInt2 < 0) ? tmpInt2 * -1 : tmpInt2;
  // Then print as parts using sprintf - Note 0 padding for fractional bit
  //  sprintf(headingString, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);
  sprintf(headingString, "%d.%04d", tmpInt1, tmpInt2);
}


void plotEncoder() {
  // calcHeading(rotaryCount);
  char buffer[64];
  sprintf(buffer, "%u, %s, %i ", rotaryCount, headingString, rpm);    // Needs %u for UNSIGNED
  Serial.println(buffer);
}


// Function counts encoder pulses and determines the direction of the encoder
void encoderDirection() {
  prevCount = rotaryCount;
  if (fired)  {
    if (up) {
      rotaryCount++;
    } else {
      rotaryCount--;
    }
    fired = false;
  }  // end if fired

  if (rotaryCount > prevCount) {          //
    clockwiseRotation = true;                      //
  } else if (rotaryCount < prevCount) {             // Not ideal as how does it cope with rollover?! // Will it work having this here first, then doing the rollaround?
    clockwiseRotation = false;
  }

  if (rotaryCount < 500) {
    rotaryCount = 1500;
  } else if (rotaryCount > 1500) {
    rotaryCount = 500;
  }
}




void isr () {
  if (digitalRead (PIN_A)) {                 // if change is detected on interrupt pin
    up = !digitalRead (PIN_B);
  } else {
    up = digitalRead (PIN_B);
  }
  fired = true;
}




/*
   Printing Floats



  char str[100];
  float adc_read = 678.0123;

  char *tmpSign = (adc_read < 0) ? "-" : "";
  float tmpVal = (adc_read < 0) ? -adc_read : adc_read;

  int tmpInt1 = tmpVal;                  // Get the integer (678).
  float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
  int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

  // Print as parts, note that you need 0-padding for fractional bit.

  sprintf (str, "adc_read = %s%d.%04d\n", tmpSign, tmpInt1, tmpInt2);


*/
