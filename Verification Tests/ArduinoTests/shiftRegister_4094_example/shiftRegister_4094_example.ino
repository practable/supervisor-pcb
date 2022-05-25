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

// SPI Capable pins
#define latchPin 8
#define clockPin 13
#define dataPin 11


// Difference between arduino pin numbers and shiftregister pin numbers is save as unsigned char type instead of int or use these #defs directly
#define D14 B00000001
#define D15 B00000010
#define D16 B00000100
#define D17 B00001000
#define D18 B00010000
#define D19 B00100000
#define D20 B01000000
#define D21 B10000000

#define STUDENT_MOTOR_ENABLE D14   // Even more descriptive names can then be used to match function with the new digital pin numbers.

unsigned char shiftPinArray[9] = {D14, D15, D16, D16, D17, D18, D19, D20};

// Program Variables

unsigned char initState   = B00100000;
unsigned char newerData   = B00000011;
unsigned char testBitmask = B00000010;

unsigned char expectedOut = B00000010;

unsigned char unsetBits   = B11111101;

unsigned char flipMask    = B00100101;

unsigned char shiftState = B00000000;   // Global Variable to hold the state of the shiftRegister

void setup() {
  begin();
  Serial.println("\n\n");
  shiftWrite(STUDENT_MOTOR_ENABLE, HIGH);
  delay(1000);
  Serial.println("\n\n");
  shiftWrite(D15, HIGH);
  delay(1000);
  Serial.println("\n\n");
  shiftWrite(D16, HIGH);
  delay(1000);
  Serial.println("\n\n");
  shiftWrite(D14, LOW);
  delay(2000);

  for (int i = 0; i < 8; i++) {
    shiftWrite(shiftPinArray[i], LOW);
    delay(200);
  }

  delay(4000);
  for (int i = 0; i < 8; i++) {
    shiftWrite(shiftPinArray[i], HIGH);
    delay(200);
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    shiftWrite(shiftPinArray[i], LOW);
    delay(200);
  }

}



void loop() {


  // Nothing here
}






// Aims to mirror the function of digitalWrite but for shift register channels
void shiftWrite(unsigned char bitmask, bool state) {
  if (state) {
    shiftState = setBits(shiftState, bitmask);
  } else {
    bitmask = flipAllBits(bitmask);
    shiftState = clearBits(shiftState, bitmask);
  }
  overwriteOutput(shiftState);
}






// Only sets 1 bits in bitmask, leaves others unchanged
unsigned char setBits(unsigned char currentData, unsigned char bitmask) {
  //  printByte(currentData);
  //  printByte(bitmask);
  currentData |= bitmask;
  //  printByte(currentData);
  return currentData;
}

// Only resets 0 bits in bitmask, leaves others unchanged
unsigned char clearBits(unsigned char currentData, unsigned char bitmask) {
  //  printByte(currentData);
  //  printByte(bitmask);
  currentData &= bitmask;
  //  printByte(currentData);
  return currentData;
}


// Flips all 1 bits using bitmask
unsigned char flipBits(unsigned char currentData, unsigned char bitmask) {
  //  printByte(currentData);
  // printByte(bitmask);
  currentData ^= bitmask;
  /// printByte(currentData);
  return currentData;
}



// Flips all the bits in a byte - very useful for generating bitmasks for mirroring digtalWrite function for shift register
unsigned char flipAllBits(unsigned char bits) {
  bits = flipBits(bits, B11111111);
  return bits;
}



// Prints chars or bytes in binary for easy debugging
void printByte(unsigned char bite) {
  char  buffer[2];
  for (int i = 0; i < 8; i++) {
    sprintf(buffer, "%d", !!((bite << i) & 0x80));
    Serial.print(buffer);
  }
  Serial.print("\n");
}



// Function outputs the exact byte passed to shift register, regardless of previous data
// Note the only function that actually outputs to hardware so far - the rest are software functions only. 
// It is best (at the moment) to track the current state of the shiftRegisters outputs, and use this to update this global byte, unless you want to totally
// overwrite all shift register outputs
void overwriteOutput(unsigned char bite) {
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, bite);
  digitalWrite(latchPin, LOW);
}



void begin() {
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
