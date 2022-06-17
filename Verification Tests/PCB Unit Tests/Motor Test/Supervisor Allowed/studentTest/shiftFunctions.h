/* shiftFunctions.h

    Just a place to store shift register functiosn defined outside of the class

    Shift Register Pins:

      For Control:
          #define MOSI                11
          #define SCK                 13
          #define LATCH               8

      Output Pins:
          #define DC_MOTOR_EN          Q0
          #define STUDENT_M_EN         Q1
          #define STUDENT_STEP_EN      Q2
          #define STUDENT_PIXEL_EN     Q3
          #define STEPP_DIR            Q4
          #define STEPP_EN             Q5
          #define STEPP_RST            Q6
          #define SHIFT_REG_7          Q7


*/


#ifndef shiftFunctions_h
#define shiftFunctions_h

#include "shiftRegister.h"        // shiftRegister Library 

shiftRegister shiftReg(MOSI, SCK, LATCH);  // Shift Register object









#endif
