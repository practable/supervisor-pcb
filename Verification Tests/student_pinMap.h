/*  #Remote Labs Supervisor MCU PinMap
*   
*	Imogen Heard
*	25/05/2022
*
*/

#ifndef supervisor_pinMap_h
#define supervisor_pinMap_h


#include "shiftRegister_pinMap.h"

// Arduino Compatable Pins


#define ENCODER_B				D2
#define ENCODER_A				D3
#define ENCODER_INDEX			D4
#define PIXEL_DATA				D5
#define STEPP_STEP 				D6
#define DC_MOTOR_DIR2			D7
#define LATCH					D8
#define SERVO_1					D9
#define DC_MOTOR_PWM			D10
#define	MOSI					D11
#define DC_MOTOR_DIR1			D12
#define SCK						D13
#define SPARE_1					D15     // <- not the same as Supervisor
#define LIMIT_1					D18
#define STEPP_FLT				D19

#define SPARE_2					A2
#define THERMO					A3
#define DC_MOTOR_IS2			A6
#define DC_MOTOR_IS1			A7


// Shift Register Pins (Needs shift register functions and pin bitmask declaration header (shiftRegister_pinMap.h) to validate)

#define DC_MOTOR_EN				Q0
#define SHIFT_1					Q1
#define SHIFT_2					Q2
#define SHIFT_3					Q3
#define STEPP_DIR				Q4
#define STEPP_EN				Q5
#define STEPP_RST				Q6
#define SHIFT_REG_7				Q7












#endif