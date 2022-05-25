/* shiftRegister.h

    Simple API for interacting with a 4094 shift register, and accessing pins in a similar manner to other arduino pins.

    Imogen Heard
    5.05.2022


*/




#ifndef shiftRegister_h
#define shiftRegister_h

#if (ARDUINO >=100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif


#include "shiftRegister_pinMap.h"

class shiftRegister
{
  public:

    // constructor
    shiftRegister(char pico_pin = 11, char sck_pin = 13, char latch_pin = 8);

    // Methods

    void begin(uint16_t baudrate = 115200);                                               // Begin function sets up output pins

    void allWrite(unsigned char pinNumber, bool state);                                   // aims to tie shiftWrite and digitalWrite together such that any pinnumber can be passed to set the correct output. Making operation seamless between shift register pins and arduino

    void shiftWrite(unsigned char bitmask, bool state);                                   // Mirrors function of digitalWrite for shiftRegister channels

    void printByte(unsigned char bite);                                                   // Prints chars or bytes in binary for easy debugging


    // Function outputs the exact byte passed to shift register, regardless of previous data
    // Note the only function that actually outputs to hardware so far - the rest are software functions only.
    // It is best (at the moment) to track the current state of the shiftRegisters outputs, and use this to update this global byte, unless you want to totally
    // overwrite all shift register outputs
    void overwriteOutput(unsigned char bite);

    void printState();                                                                    // Prints the current state of the output bits

  private:

    unsigned char setBits(unsigned char currentData, unsigned char bitmask);              // Sets 1 bits in bitmask

    unsigned char clearBits(unsigned char currentData, unsigned char bitmask);            // Only resets 0 bits in bitmask, leaves others unchanged

    unsigned char flipBits(unsigned char currentData, unsigned char bitmask);             // Flips all 1 bits using bitmask

    unsigned char flipAllBits(unsigned char bits);                                        // Flips all the bits in a byte - very useful for generating bitmasks for mirroring digtalWrite function for shift register

    char dataPin  = 11;
    char clockPin = 13;
    char latchPin = 8;


    unsigned char shiftState = B00000000;   // Global Variable to hold the state of the shiftRegister

};


#endif
