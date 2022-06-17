/*  #Remote Labs Supervisor MCU PinMap

      Imogen Heard
      25/05/2022

*/

#ifndef supervisor_pinMap_h
#define supervisor_pinMap_h



// Arduino Compatable Pins

//Inputs

#define ENCODER_B           3
#define ENCODER_A           2
#define ENCODER_INDEX       4

#define STDNT_DC_M_DIR_2    A1
#define STDNT_DC_M_DIR_1    A0

#define STEPP_FLT           A5     // D19

#define LIMIT_1             18      //A4


#define STDNT_SRVO_RX_1     A2      // STDNT_SRVO_RX_2 Only available on SAMD21 Raw

#define THERMO              A3

#define DC_MOTOR_IS2        A6
#define DC_MOTOR_IS1        A7


// Outputs

#define LED_PCB            13

#define DC_MOTOR_PWM        10
#define DC_MOTOR_DIR1       12
#define DC_MOTOR_DIR2       7

#define STEPP_STEP          6

#define SERVO_1             9

#define PIXEL_DATA          5

// Shift Register
#define MOSI                11
#define SCK                 13
#define LATCH               8



// Shift Register Pins [Output Only] (needs shiftRegister.h to validate)

/*
   shiftRegister pins are defined using Q0 - Q7 notation. This avoids pin definition conflicts with arduino pins, regardless of the platform used.
*/


#define DC_MOTOR_EN          Q0
#define STUDENT_M_EN         Q1
#define STUDENT_STEP_EN      Q2
#define STUDENT_PIXEL_EN     Q3
#define STEPP_DIR            Q4
#define STEPP_RST            Q6
#define STEPP_SLP            Q5












#endif
