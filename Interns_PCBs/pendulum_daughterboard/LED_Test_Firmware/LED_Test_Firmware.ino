int STU_LED_1 = 6;
int STU_LED_2 = 7;
int STU_LED_3 = 8;
int SUP_LED_1 = 10;
int SUP_LED_2 = 2;
int SUP_LED_3 = 9;
int STU_ENABLE = 5;
int DRIVE_IN = 12;
int LOAD_IN = 4;



void setup() {
  // put your setup code here, to run once:

  pinMode (STU_LED_1, OUTPUT);
  pinMode (STU_LED_2, OUTPUT);
  pinMode (STU_LED_3, OUTPUT);
  pinMode (SUP_LED_1, OUTPUT);
  pinMode (SUP_LED_2, OUTPUT);
  pinMode (SUP_LED_3, OUTPUT);
  pinMode (STU_ENABLE, OUTPUT);
  pinMode (DRIVE_IN, OUTPUT);
  pinMode (LOAD_IN, OUTPUT);


//flashLED();
}



void loop() {
//Initially setting all the pins low
 digitalWrite (STU_LED_1, LOW);
 digitalWrite (STU_LED_2, LOW);
 digitalWrite (STU_LED_3, LOW);
 digitalWrite (SUP_LED_1, LOW);
 digitalWrite (SUP_LED_2, LOW);
 digitalWrite (SUP_LED_3, HIGH);
 digitalWrite (STU_ENABLE, LOW);
 digitalWrite (DRIVE_IN, LOW);
 digitalWrite (LOAD_IN, LOW);

  // Trying to turn the pins on without enable

  //delay(3000);
//  digitalWrite (STU_LED_1, HIGH);
 // delay(1000);
  //digitalWrite (STU_LED_1,  LOW);
  //digitalWrite (STU_LED_2, HIGH);
 // delay(1000);
  //digitalWrite (STU_LED_2, LOW);
  //digitalWrite (STU_LED_3, HIGH);
  //delay(1000);
  //digitalWrite (STU_LED_3, LOW);
  //digitalWrite (SUP_LED_1, HIGH);
  //delay(1000);
  //digitalWrite (SUP_LED_1, LOW);
  //digitalWrite (SUP_LED_2, HIGH);
 // delay(1000);
  //digitalWrite (SUP_LED_2, LOW);
 // digitalWrite (SUP_LED_3, HIGH);

  // Trying to turn the pins on with enable
 // delay(1000);
 // digitalWrite (STU_ENABLE, HIGH);
 // delay(1000);
 // digitalWrite (SUP_LED_3, LOW);
//  digitalWrite (STU_LED_1, HIGH);
 // delay(1000);
//  digitalWrite (STU_LED_1,  LOW);
//  digitalWrite (STU_LED_2, HIGH);
//  delay(1000);
 // digitalWrite (STU_LED_2, LOW);
 // digitalWrite (STU_LED_3, HIGH);
 // delay(1000);
 // digitalWrite (STU_LED_3, LOW);
 // digitalWrite (SUP_LED_1, HIGH);
 // delay(1000);
 // digitalWrite (SUP_LED_1, LOW);
 // digitalWrite (SUP_LED_2, HIGH);
 // delay(1000);
 // digitalWrite (SUP_LED_2, LOW);
  //digitalWrite (SUP_LED_3, HIGH);



}


void flashLED() {
  int count = 6;
  while (count) {
    digitalWrite (SUP_LED_1, HIGH);
    delay(500);
    digitalWrite (SUP_LED_1,  LOW);
    delay(200);
    count--;
  }
}
