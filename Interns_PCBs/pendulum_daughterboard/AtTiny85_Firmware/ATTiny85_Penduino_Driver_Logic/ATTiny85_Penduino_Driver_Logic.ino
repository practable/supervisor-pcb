/* =====================================================
 * AtTiny85 Logic to Control the Pendulum Driver Board
 * Version 1.0
 * Date Modified: 7 July 2022
 * Written By: Bhavith Manapoty
 * bhavithmanapoty.com
 * =====================================================
 */
 
//Define Pin Numbers for the AtTiny85
#define loadInput 1
#define loadOutput 3
#define driveInput 2
#define driveOutput 4
#define LED 0

/*
 * Initialise Variables to compute Logic
 * newLoadIn stores the Load Input value of the current iteration of the loop
 * newDriveIn stores the Drive Input value of the current iteration of the loop
 * 
 * oldLoadIn stores the Load Input value of the previous iteration of the loop
 * oldDriveIn stores the Drive Input value of the previous iteration of the loop
 */
int oldLoadIn = 0;
int oldDriveIn = 0;
int newLoadIn = 0;
int newDriveIn = 0;

void setup() {
  //Initialise all INPUTS and OUTPUTS
  pinMode(loadInput, INPUT);
  pinMode(driveInput, INPUT);
  pinMode(loadOutput, OUTPUT);
  pinMode(driveOutput, OUTPUT);
  pinMode(LED, OUTPUT);

  //Give initial value to OUTPUT Pins as LOW
  digitalWrite(loadOutput, LOW);
  digitalWrite(driveOutput, LOW);
}

void loop() {
  //Reads the Load and Drive Input values of the current iteration
  newLoadIn = digitalRead(loadInput);
  newDriveIn = digitalRead(driveInput);

  //When both inputs are HIGH, outputs are LOW and error LED is switched on. State has to return to 0,0 to turn LED off
  if (newLoadIn == 1 && newDriveIn == 1)
  {
    digitalWrite(loadOutput, LOW);
    digitalWrite(driveOutput, LOW);
    digitalWrite(LED, HIGH);
  }
  //When state is currently 0,0 the new Inputs are mirrored in the outputs
  else if (oldLoadIn == 0 && oldDriveIn == 0)
  {
    digitalWrite(loadOutput, newLoadIn);
    digitalWrite(driveOutput, newDriveIn);
  }
  //When state is not 0,0 the only acceptable new state is 0,0. This will also switch off error LED if it is on.
  else
  {
    if (newLoadIn == 0 && newDriveIn == 0)
    {
      digitalWrite(loadOutput, newLoadIn);
      digitalWrite(driveOutput, newDriveIn);
      digitalWrite(LED, LOW);
    }
  }

  //Saves the current iteartion input values as the old values and continues loop
  oldLoadIn = newLoadIn;
  oldDriveIn = newDriveIn;
}
