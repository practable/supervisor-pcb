/* dcMotorFunctions.h

    Just a place to store dcMotor Functions

    DC Motor Pins
    Outputs
    #define DC_MOTOR_PWM        10
    #define DC_MOTOR_DIR1       12
    #define DC_MOTOR_DIR2       7

    Enable
    #define DC_MOTOR_EN         Q0

    Sense Pins
    #define DC_MOTOR_IS2        A6
    #define DC_MOTOR_IS1        A7

    Student to Supervisor Pins    //
    #define STDNT_DC_M_DIR_2    14
    #define STDNT_DC_M_DIR_1    15


    DC Motor Datasheets
    https://docs.rs-online.com/91cb/0900766b81490d99.pdf
    https://docs.rs-online.com/9aef/0900766b81490db0.pdf
    https://docs.rs-online.com/6a9d/0900766b81478095.pdf


*/


#ifndef dcMotorFunctions_h
#define dcMotorFunctions_h




// DC Motor Driver Board control
void dcMotorBegin() {
  pinMode(DC_MOTOR_PWM, OUTPUT);
  pinMode(DC_MOTOR_DIR1, OUTPUT);
  pinMode(DC_MOTOR_DIR2, OUTPUT);
}





// Enable must be high to actuate motor  (Needs shift register library to access)
void dcMotorEnable(bool state) {
  shiftReg.shiftWrite(DC_MOTOR_EN, state);
}





// Direction Control DC Motor
/*
  // Notes on H-Bridge Drivers https://www.modularcircuits.com/blog/articles/h-bridge-secrets/h-bridges-the-basics/
  // Additional Information on dead time insertion https://hackaday.io/project/3176-gator-quad/log/11741-pwm-control-and-dead-time-insertion

  As I am lazy I am just going to use the value at the end of the hackaday article as a baseline deadtime 1.5x10^-7 seconds which is microseconds,
  so a delay time of just a few milliseconds should be sufficient to avoid shootthrough
*/

#define DEADTIME_MS 10
void dcMotorDirection(bool clockwise = true) {
  digitalWrite(DC_MOTOR_DIR1, LOW);
  digitalWrite(DC_MOTOR_DIR2, LOW);
  delay(DEADTIME_MS);
  if (clockwise) {
    digitalWrite(DC_MOTOR_DIR1, HIGH);
  } else {
    digitalWrite(DC_MOTOR_DIR2, HIGH);
  }
}





// Change motor drive level.
// Further reading on PWM Output incase we need to change PWM frequency https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm
#define MAX_MOTOR_SPEED 255                                  // Set a max drive level to constrain motor speed
void dcMotorSpeed(uint16_t pwmOut = 0) {
  pwmOut = constrain(pwmOut, 0, MAX_MOTOR_SPEED);
  analogWrite(DC_MOTOR_PWM, pwmOut);
}


// DONT FORGET ABOUT CURRENT SENSING
// NOTE This has both a Sense current and a step increase to a fault current. If fault current is detected, flag should be raised.
// https://docs.rs-online.com/6a9d/0900766b81478095.pdf See page 18 for details.

/*  Sense Current Algorithm
    I_IS = (1/dk_ILIS)*I_L + IS_OFFSET

    Load Current from Sense Current

    I_L = dk_ILIS*(I_IS - IS_OFFSET)

    differential current sense ratio dk_ILIS is defined as:

    dk_ILIS = (I_L2 - I_L1) / (I_IS(I_L2)) - (I_IS(I_L1))


    I_IS = V_IS / R_IS

    V_IS is measured voltage
    R_IS is current sink resistors 470r

    as 3.3v is ADC max @ 1024

    3.3/1024 = 33/10240
*/




#define ADC_VMAX          3.3
#define ADC_MAXVALUE      1024.0


float analogToVoltage(int16_t analogValue) {
  float voltage = float(analogValue) * float(ADC_VMAX / ADC_MAXVALUE);
  return voltage;
}

//   I_IS = V_IS / R_IS
float voltageToCurrent(float voltage, int16_t resistance) {
  float current_mA = (voltage / float(resistance)) * 1000.0;
  return current_mA;
}



#define IS_OFFSET_uA      170
#define DK_ILIS           19.5e3     // Can be caclulated but unsure how. taken typical value for now
float senseCurrent_loadCurrent(float senseCurrent_mA) {
  senseCurrent_mA = senseCurrent_mA - (IS_OFFSET_uA * 10e-3);   // FIRST subtract the offset current 10^-3 because we need mA not A (10e-6)
  float loadCurrent_mA = senseCurrent_mA * DK_ILIS;
  return loadCurrent_mA;
}



void showCalculations(int16_t adc, float volts, float I_sense, float I_load) {
  Serial.print("ADC Read: ");
  Serial.print(adc);
  Serial.print("   ADC to Voltage: ");
  Serial.print(volts);
  Serial.print("   voltage to (sense)Current: ");
  Serial.print(I_sense);
  Serial.print(" mA ");
  //  Serial.print("   senscurrent - offset: ");
  //  Serial.print(senseCurrent_mA);
  //  Serial.print(" mA ");
  Serial.print("   LoadCurrent: ");
  Serial.print(I_load);
  Serial.println(" mA ");
}



#define R_IS              470
#define SHOW_MOTOR_CALCS          false                      // Additional Debug outputs

float adc_to_loadCurrent(int16_t adcValue) {
  float volts = analogToVoltage(adcValue);                             // Convert to measured voltage
  float senseCurrent_mA = voltageToCurrent(volts, R_IS);               // Convert voltage to current(mA) using I = V/R
  float loadCurrent_mA = senseCurrent_loadCurrent(senseCurrent_mA);      // Use Datasheet Algorithm to estimate load current in mA
  if (SHOW_MOTOR_CALCS) {
    showCalculations(adcValue, volts, senseCurrent_mA, loadCurrent_mA);
  }
  return loadCurrent_mA;
}









// Ties all hardware and maths functions together for DC Motor Current Sensing

autoDelay printDelay;
#define PRINT_DELAYTIME

void dcMotorCurrent(bool active) {
  if (active) {
    if (printDelay.millisDelay(500)) {
      int16_t adcReadOne = analogRead(DC_MOTOR_IS1);                              // Take ADC Sample
      int16_t adcReadTwo = analogRead(DC_MOTOR_IS2);
      float f_loadCurrentOne_mA = adc_to_loadCurrent(adcReadOne);
      int i_loadCurrentOne_mA = int(f_loadCurrentOne_mA + 0.5);                             // cast float value back to int for easy printing
      float f_loadCurrentTwo_mA = adc_to_loadCurrent(adcReadTwo);
      int i_loadCurrentTwo_mA = int(f_loadCurrentTwo_mA + 0.5);                             // cast float value back to int for ea

      char buffer[64];
      sprintf(buffer, "Load Current One: %i mA, Load Current Two: %i mA", i_loadCurrentOne_mA, i_loadCurrentTwo_mA);
      Serial.println(buffer);
    }
  }
}

/*
   Overtemp lockout state is latched until the device is reset by a low signal with a
   minimum length of treset at the INH pin, provided that its temperature has decreased at least the thermal hysteresis
   ΔT in the meantime

*/
void overTempReset() {

}



#endif
