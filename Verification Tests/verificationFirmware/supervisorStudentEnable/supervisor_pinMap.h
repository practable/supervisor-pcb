/*  #Remote Labs Supervisor MCU PinMap
*   
*     Imogen Heard
*     25/05/2022
*
*/

#ifndef supervisor_pinMap_h
#define supervisor_pinMap_h


#include "shiftRegister_pinMap.h"

// Arduino Compatable Pins

//Inputs
  
#define ENCODER_B           D2
#define ENCODER_A           D3
#define ENCODER_INDEX       D4

#define STDNT_DC_M_DIR_2    D14
#define STDNT_DC_M_DIR_1    D15

#define STEPP_FLT           D19

#define LIMIT_1             D18


#define STDNT_SRVO_RX_1     A2      // STDNT_SRVO_RX_2 Only available on SAMD21 Raw

#define THERMO              A3

#define DC_MOTOR_IS2        A6
#define DC_MOTOR_IS1        A7


// Outputs

#define DC_MOTOR_PWM        D10
#define DC_MOTOR_DIR1       D12
#define DC_MOTOR_DIR2       D7

#define STEPP_STEP          D6

#define SERVO_1             D9

#define PIXEL_DATA          D5

#define MOSI                D11
#define SCK                 D13
#define LATCH               D8



// Shift Register Pins (Needs shift register functions and pin bitmask declaration header (shiftRegister_pinMap.h) to validate)

#define DC_MOTOR_EN          Q0
#define STUDENT_M_EN         Q1
#define STUDENT_STEP_EN      Q2
#define STUDENT_PIXEL_EN     Q3
#define STEPP_DIR            Q4
#define STEPP_EN             Q5
#define STEPP_RST            Q6
#define SHIFT_REG_7          Q7












#endif
