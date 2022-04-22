/*   shiftregister 4094

      Test Program 4094 Shift Register

      Simple API for expanding arduino digital outputs using
      predictable naming

      Imogen Heard 22/04/2022

      Test for Supervisor PCB for practicable.io remote Lab Experiments

  http://ediy.com.my/blog/item/114-using-hef4094-shift-registers-with-arduino
*/




// Pin Declarations

// Output Pins

// PWM Capable
#define latchPin 8
#define clockPin 13
#define dataPin 11




// Program Variables

unsigned char initState   = B00100000;
unsigned char newerData   = B00000011;
unsigned char testBitmask = B00000010;

unsigned char expectedOut = B00000010;

void setup() {
  begin();
  Serial.println("\n\n");
//  overwriteOutput(B10100000);
  //Serial.println(initState);
  unsigned char newState = bitMask(initState, testBitmask);
  //Serial.println(newState);

}



void loop() {


  // Nothing here
}

// Function outputs the exact byte passed
void overwriteOutput(unsigned char bite) {
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, bite);
  digitalWrite(latchPin, HIGH);
}

// Function only updates outputs set in bitmask
void updateOutput(unsigned char bite, unsigned char bitmask) {


}





// Only sets bits in bitmask, leaves others unchanged
unsigned char bitMask(unsigned char currentData, unsigned char bitmask) {
  printByte(currentData);
  printByte(bitmask);

  currentData |= bitmask;

  printByte(currentData);

  return currentData;
}


void printByte(unsigned char bite) {
  char  buffer[2];
  for (int i = 0; i < 8; i++) {
    sprintf(buffer, "%d", !!((bite << i) & 0x80));
    Serial.print(buffer);
  }
  Serial.print("\n");
}



void begin() {
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
