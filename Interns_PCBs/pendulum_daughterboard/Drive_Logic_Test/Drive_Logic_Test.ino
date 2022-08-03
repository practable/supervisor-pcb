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


}

void loop() {
  // put your main code here, to run repeatedly:

 digitalWrite (DRIVE_IN, LOW);
 digitalWrite (LOAD_IN, LOW);

 if (digitalRead(DRIVE_IN) == LOW  && digitalRead(LOAD_IN) == LOW)
  {
    digitalWrite(SUP_LED_1, HIGH);
  }

  if ( digitalRead(DRIVE_IN) == HIGH  && digitalRead(LOAD_IN) == LOW)
  {
    digitalWrite(SUP_LED_2, HIGH);
  }

  if (digitalRead(DRIVE_IN) == LOW  && digitalRead(LOAD_IN) == HIGH)
  {
    digitalWrite(SUP_LED_3, HIGH);
  }

  
  if (digitalRead(DRIVE_IN) == HIGH  && digitalRead(LOAD_IN) == HIGH)
  {
    digitalWrite(SUP_LED_3, HIGH);
    digitalWrite(SUP_LED_1, HIGH);
    digitalWrite(SUP_LED_2, HIGH);
  }


}
