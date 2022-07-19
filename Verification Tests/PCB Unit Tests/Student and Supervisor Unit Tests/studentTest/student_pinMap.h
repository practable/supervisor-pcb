/*  #Remote Labs Supervisor MCU PinMap
*   
*	Imogen Heard
*	25/05/2022
*
*/

#ifndef supervisor_pinMap_h
#define supervisor_pinMap_h




// Arduino Compatable Pins


#define ENCODER_B				    2
#define ENCODER_A				    3
#define ENCODER_INDEX		   	4
#define PIXEL_DATA				  5
#define STEPP_STEP 				  6
#define DC_MOTOR_DIR2			  7
#define LATCH				      	8
#define SERVO_1					    9
#define DC_MOTOR_PWM		   	10
#define	MOSI					      11
#define DC_MOTOR_DIR1			  12
#define SCK						      13
#define SPARE_1					    15     // <- not the same as Supervisor
#define LIMIT_1					    18
#define STEPP_FLT			    	19

#define SPARE_2	    				A2
#define THERMO				    	A3
#define DC_MOTOR_IS2	  		A6
#define DC_MOTOR_IS1	  		A7


// Shift Register Pins (Needs shiftRegister.h to validate)

#define DC_MOTOR_EN			  	Q0
#define SHIFT_1	    				Q1
#define SHIFT_2			    		Q2
#define SHIFT_3			    		Q3
#define STEPP_DIR			    	Q4
#define STEPP_SLP	    			Q5
#define STEPP_RST	    			Q6
#define SHIFT_REG_7		   		Q7












#endif
