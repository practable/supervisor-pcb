/* servoFunctions.h

    Just a place to store Servo Motor Functions

    Notes on Servo Operation without library:
    https://forum.arduino.cc/t/how-to-use-servos-without-servo-h-library/567244/13

    20mS between pulses - 50Hz
    1 - 2mS pulses control servo position
    1.5mS =   0 deg
    1ms   =  -90 deg
    2mS   =   90 deg

    digitalWrite command ~ 3uS - probably insignificant amount of delay to add to calculations


    Servo Pins

    Output:
    #define SERVO_1             9

    Input from Student
    #define STDNT_SRVO_RX_1     A2

    Okay - Servo hardware works but I cannot work out how to control this. maybe clock speed needs looking at because it seems to be behaving very poorly

*/


#ifndef servoFunctions_h
#define servoFunctions_h



#include <Servo.h>

Servo servo;


#define SERVO_1             9


void servoBegin() {
  servo.attach(SERVO_1);
}


int16_t servoMin = -90;            // Upper and Lower limits of Servo Operation
int16_t servoMax = 90;

// Change upper and Lower Constraints
void servoConstrain(int16_t minTravel, int16_t maxTravel) {
  servoMin = minTravel;
  servoMax = maxTravel;
}


bool servoBlocking;
int32_t servoBlockTime_mS = 20;
int32_t servoLastUpdate;

void servoUpdate(int16_t angle = 0) {    // can pass values between -90 and +90  // Servo library wants between 0 and 180
  if (!servoBlocking) {
    int16_t new_angle = angle + 90;
    new_angle = constrain(new_angle, servoMin, servoMax);
    servo.write(new_angle);
    servoLastUpdate = millis();
    servoBlocking = true;
  }
  if (millis() -  servoLastUpdate >= servoBlockTime_mS) {
    servoBlocking = false;
  }
}





void servoTest(bool active = false){
  if (active){
    servoUpdate();
  }
}












// All this stuff made things do things but not what I was aming for :(

/*

  #include <autoDelay.h>


  autoDelay servoDelay;
  autoDelay servoBlocking;   // delay between writing to the servo output


  bool servoMoving;
  int32_t servoMoveTime_mS = -1;     // Timeout timer for servo updates (-1 for no timeout)
  int32_t servoStartMoveTime_mS;
  int16_t servoPos_deg = 0;          // global variable to track servo positoon
  uint32_t servoPulseLength;          // the output pulse length for the PPM servo control

  int16_t servoMin = -180;            // Upper and Lower limits of Servo Operation
  int16_t servoMax = 180;

  // Begin Function
  void servoBegin() {
  pinMode(SERVO_1, OUTPUT);
  servoPulseLength = 1500;
  }

  // Change upper and Lower Constraints
  void servoConstrain(int16_t minTravel, int16_t maxTravel) {
  servoMin = minTravel;
  servoMax = maxTravel;
  }


  // Update the target position of the servo and return the pulse time for the output
  uint32_t servoPosition(int16_t new_servoPos_deg) {
  new_servoPos_deg = constrain(new_servoPos_deg, servoMin, servoMax);     // Constrain the value to the possible range of motion of the servo
  uint32_t pulseHigh_uS;
  pulseHigh_uS = map(new_servoPos_deg, servoMin, servoMax, 1000, 2000);                // Map servo position to a value of the high pulse in uS (1000 - 2000 uS)

  if (new_servoPos_deg == servoPos_deg) {                                     // If the new position is the same as old position exit function
    return  pulseHigh_uS;                                                  // Return the pulse value, but dont set the bool to tell output that the servo needs to move
  }
  servoPos_deg = new_servoPos_deg;
  //  Serial.println(pulseHigh_uS);
  servoMoving = true;
  servoStartMoveTime_mS = millis();
  return pulseHigh_uS;
  }



  bool servoPulseState;

  #define SERVO_BLOCKING_TIME_mS 10                                                // Blocking for output update - fix to solve over hunting and heating

  // Outputs the pulses to control the servo
  void servoOutput(uint32_t pulseTime_uS = 1500) {
  if (!servoMoving) {
    return;
  }
  if (!servoBlocking.millisDelay(SERVO_BLOCKING_TIME_mS)) {                  // Slows down individual updates to servo position to avoid hunting
    return;
  }
  bool pulseStateChanged;
  if (servoMoveTime_mS > 0) {                                                // Timer to block updates after a timeout set time to -1 to disable i.e. updates never timeout
    if (millis() - servoStartMoveTime_mS >= servoMoveTime_mS) {
      servoMoving = false;
      return;
    }
  }
  if (!servoPulseState) {                                    // if the pulse is low - time for 20mS-pulseTime? - dont know if needed or not. got louder last time I added this
    if (servoDelay.microsDelay(2000 - pulseTime_uS)) {
      servoPulseState = HIGH;
      pulseStateChanged = true;
    }
  } else {
    if (servoDelay.microsDelay(pulseTime_uS)) {             // else time the high pulse for pulseTime_uS
      servoPulseState = LOW;
      pulseStateChanged = true;
    }
  }
  if (!pulseStateChanged) {                                      // if the state of the pulse hasnt changed dont bother to perform digitalwrite operation
    return;
  }
  digitalWrite(SERVO_1, servoPulseState);
  }




  // Ties servoPositon and servoOutput into a single function, which will only update the servo if the position changes.
  void servoUpdate(int16_t newPosition_deg) {
  uint32_t servoPulseTimer = servoPosition(newPosition_deg);
  servoOutput(servoPulseTimer);
  }




  #define NEW_POS_TIME_S 5            // Time between New Positions (Seconds)

  autoDelay testDelay;
  // Applies random updates to the servo to test
  void servoTest(bool active = false) {
  if (!active) {
    return;
  }
  if (testDelay.secondsDelay(NEW_POS_TIME_S)) {
    int randomInt = random(-180, 180);                    // Generates random positions that may be outside of servo range of movement, but no problem because of constrain
    Serial.print("New Servo Angle: ");
    Serial.println(randomInt);
    servoPulseLength = servoPosition(randomInt);
  }
  servoOutput(servoPulseLength);                 // Needs to be in loop
  }

*/

#endif
