/* shiftRegister.cpp

    Simple API for interacting with a 4094 shift register, and accessing pins in a similar manner to other arduino pins.

    Imogen Heard
    5.05.2022


*/


#include "shiftRegister.h"


// Constructor
// Passes pin definitions to shiftRegister Object

shiftRegister::shiftRegister(char pico_pin, char sck_pin, char latch_pin):
  dataPin(pico_pin),
  clockPin(sck_pin),
  latchPin(latch_pin)
{
}


void shiftRegister::begin(uint16_t baudrate) {
  Serial.begin(baudrate);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}


// Aims to mirror the function of digitalWrite but for shift register channels
void shiftRegister::shiftWrite(unsigned char bitmask, bool state) {
  if (state) {
    shiftState = setBits(shiftState, bitmask);
  } else {
    bitmask = flipAllBits(bitmask);
    shiftState = clearBits(shiftState, bitmask);
  }
  overwriteOutput(shiftState);
}




// Function outputs the exact byte passed to shift register, regardless of previous data
// Note the only function that actually outputs to hardware so far - the rest are software functions only.
// It is best (at the moment) to track the current state of the shiftRegisters outputs, and use this to update this global byte, unless you want to totally
// overwrite all shift register outputs
void shiftRegister::overwriteOutput(unsigned char bite) {
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, MSBFIRST, bite);
  digitalWrite(latchPin, LOW);
}

#define LARGEST_PINNUMBER D30

// aims to tie shiftWrite and digitalWrite together such that any pinnumber can be passed to set the correct output.
// Making operation seamless between shift register pins and arduino
// VERY UNTESTED
// Probably need a better way of doing this
void shiftRegister::allWrite(unsigned char pinNumber, bool state) {
  if (pinNumber >= LARGEST_PINNUMBER) {
    shiftRegister::shiftWrite(pinNumber, state);
  } else {
    digitalWrite(pinNumber, state);
  }
}



// Bit operations used in backend to update the shiftState variable

// Only sets 1 bits in bitmask, leaves others unchanged
unsigned char shiftRegister::setBits(unsigned char currentData, unsigned char bitmask) {
  currentData |= bitmask;
  return currentData;
}

// Only resets 0 bits in bitmask, leaves others unchanged
unsigned char shiftRegister::clearBits(unsigned char currentData, unsigned char bitmask) {
  currentData &= bitmask;
  return currentData;
}


// Flips all 1 bits using bitmask
unsigned char shiftRegister::flipBits(unsigned char currentData, unsigned char bitmask) {
  currentData ^= bitmask;
  return currentData;
}



// Flips all the bits in a byte - very useful for generating bitmasks for mirroring digtalWrite function for shift register
unsigned char shiftRegister::flipAllBits(unsigned char bits) {
  bits = flipBits(bits, B11111111);
  return bits;
}



// Prints chars or bytes in binary for easy debugging
void shiftRegister::printByte(unsigned char bite) {
  char  buffer[2];
  for (int i = 0; i < 8; i++) {
    sprintf(buffer, "%d", !!((bite << i) & 0x80));
    Serial.print(buffer);
  }
  Serial.print("\n");
}


void shiftRegister::printState() {
  shiftRegister::printByte(shiftState);
}
