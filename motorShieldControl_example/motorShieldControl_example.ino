/*   motorShield Control

      Test Program for infineon BT8982_dev.2 Arduino Shield


      Ramps motor speed up slowly in one direction,
      waits for t time to allow motor to slow
      Ramps motor speed up slowly in other direction
      waits for t time to allow motor to slow

      This should prevent motor from approaching stall current and will minimise requirements for testing

      Imogen Heard 18/04/2022

      Test for Supervisor PCB for practicable.io remote Lab Experiments


*/


/*   motorShield Control

      Test Program for infineon BT8982_dev.2 Arduino Shield


      Ramps motor speed up slowly in one direction,
      waits for t time to allow motor to slow
      Ramps motor speed up slowly in other direction
      waits for t time to allow motor to slow

      This should prevent motor from approaching stall current and will minimise requirements for testing

      Imogen Heard 18/04/2022

      Test for Supervisor PCB for practicable.io remote Lab Experiments


*/



// Pin Declarations

// Output Pins

// PWM Capable
#define IN_1    11
#define IN_2    9

// Inhibit pins - Pull high to activate
#define INH_1   10
#define INH_2   6

int16_t pwmPins[2] = {IN_1,IN_2};

// Input Pins
// ADC
#define IS_1    A0
#define IS_2    A1


// Program Variables

#define RAMP_DELAY_S 20  // Total ramp up speed from 0 to VMAX - limits total current draw
#define VMAX 50  // Maximum PWM output for motor speed ramp - limits total current draw
#define FREE_RUN_TIME_S 5  // Total free run time before ramping motor speed in opposite direction - to avoid motor reaching stall current

int32_t ramp_step_delay_mS;

int16_t motorSpeed = 0;
uint8_t pwmValue;

int16_t is1_val;
int16_t is2_val;
bool activePins[2] = {0, 0};

#include <autoDelay.h>
autoDelay autoDelay;


enum progState {
  AT_REST,
  RAMP_UP,
  REST_F,
  RAMP_DOWN,
  REST_B
};

uint8_t currentState = AT_REST;


void activateDrive(bool inh1, bool inh2){
  digitalWrite(INH_1, inh1);
  digitalWrite(INH_2, inh2);
}


void setMotorOutputs() {
  calcPWM();
  applyPWMtoActivePins();
}

void calcPWM() {
  if (motorSpeed > 0) {
    pwmValue = constrain(motorSpeed, 0, VMAX);
    changeActivePins(1, 0);
  } else if (motorSpeed < 0) {
    pwmValue = constrain((motorSpeed * -1), 0 , VMAX);
    changeActivePins(0, 1);
  } else {
    pwmValue = 0;
    changeActivePins(0, 0);
  }
}


// This is overkill. Instead PWM is fed to both pins on the motor driver board, and the INH pins disable the direction that is not required
void applyPWMtoActivePins() {
  for (int i = 0; i < 2; i++) {
    if (activePins[i]) {
      analogWrite(pwmPins[i], pwmValue);
    } else {
      analogWrite(pwmPins[i], 0);
    }
  }
}

void changeActivePins(bool in1, bool in2) {
  activePins[0] = in1;
  activePins[1] = in2;
}

void stateSelect(uint8_t state = AT_REST) {
  switch (state) {
    case RAMP_UP:
      rampUp();
      break;
    case REST_F:
      restF();
      break;
    case RAMP_DOWN:
      rampDown();
      break;
    case REST_B:
      restB();
      break;
    case AT_REST:
      atRest();
      break;
    default:
      atRest();
      // Same as AT_REST
      break;
  }
}

uint32_t calcStepDelayTime(uint16_t rampDelayS = 60) {
  uint32_t stepDelay_mS = (rampDelayS * 1000) / (VMAX);
  Serial.println(stepDelay_mS);
  return stepDelay_mS;
}

void rampUp() {
  if (autoDelay.millisDelay(ramp_step_delay_mS)) {
    motorSpeed = motorSpeed + 1;
  }
  if (motorSpeed >= VMAX) {
    Serial.println("State: REST_F");
    motorSpeed = 0;
    currentState = REST_F;
  }
}

void restF() {
  if (autoDelay.secondsDelay(FREE_RUN_TIME_S)) {
    Serial.println("State: RAMP_DOWN");
    currentState = RAMP_DOWN;
  }
}

void rampDown() {
  if (autoDelay.millisDelay(ramp_step_delay_mS)) {
    motorSpeed = motorSpeed - 1;
  }
  if (motorSpeed <= (-1 * VMAX)) {
    Serial.println("State: REST_B");
    motorSpeed = 0;
    currentState = REST_F;
  }
}

void restB() {
  if (autoDelay.secondsDelay(FREE_RUN_TIME_S)) {
    Serial.println("State: RAMP_UP");
    currentState = RAMP_UP;
  }
}

void atRest() {
  motorSpeed = 0;
}



void printHeader() {
  Serial.println("motorSpeed, pwmValue, IS_1, IS_2");
}


void plotReadings() {
  char buffer[64];
  sprintf(buffer, "motorSpeed: %i, pwmValue: %i ,IS_1: %i, IS_2: %i, ", motorSpeed, pwmValue, is1_val, is2_val);
  Serial.println(buffer);
}

void sampleADCs() {
  is1_val = analogRead(IS_1);
  is2_val = analogRead(IS_2);
}

void setup() {
  Serial.begin(115200);
  pinMode(IN_1, OUTPUT);
  pinMode(INH_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(INH_2, OUTPUT);

  // Calculate Ramp Step Delay
  ramp_step_delay_mS = calcStepDelayTime(RAMP_DELAY_S);
  printHeader();
  currentState = RAMP_UP;
  //currentState = AT_REST;
  activateDrive(1,1);
}





void loop() {
  stateSelect(currentState);
  setMotorOutputs();
  sampleADCs();
  plotReadings();
}
