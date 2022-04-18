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
#define INH_1   10
#define IN_2    9
#define INH_2   6

// Input Pins
// ADC
#define IS_1    A0
#define IS_2    A1


// Program Variables

#define RAMP_UP_DELAY_S 60  // Total ramp up speed from 0 to V_MAX - limits total current draw
#define V_MAX 100   // Maximum PWM output for motor speed ramp - limits total current draw
#define FREE_RUN_TIME_S 60  // Total free run time before ramping motor speed in opposite direction - to avoid motor reaching stall current

int32_t ramp_step_delay; 

int16_t motorSpeed = 0;
uint8_t pwmValue;

autoDelay autoDelay;


enum progState {
  AT_REST,
  RAMP_UP,
  REST_F,
  RAMP_DOWN,
  REST_B
};

uint8_t currentState = AT_REST;


void setup() {
  Serial.begin(115200);
  pinMode(IN_1, OUTPUT);
  pinMode(INH_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(INH_2, OUTPUT);

  // Calculate Ramp Step Delay
  printHeader();
  currentState = RAMP_UP;
}





void loop() {
  plotReadings();
  currentState = stateSelect(currentState);
}


void stateSelect(uint8_t state = AT_REST) {
  switch (state) {
    case RAMP_UP:
      // statements
      break;
    case REST_F:
      // statements
      break;
    case RAMP_DOWN;
      // Statements
      break;
    case REST_B;
      // Statements
      break;
    case AT_REST;
      // Statements
      break;
    default:
      // statements
      // Same as AT_REST
      break;
  }
  return state;
}

void calcStepDelayTime(){
 int16_t stepDelay = 10;
 
  
}

void printHeader() {
  Serial.println("motorSpeed, pwmValue, IS_1, IS_2");
}


void plotReadings() {

  char buffer[64];
  sprintf(buffer, "motorSpeed: %i, pwmValue: %i ,IS_1: %i, IS_2: %i");
  Serial.println(buffer);
}
