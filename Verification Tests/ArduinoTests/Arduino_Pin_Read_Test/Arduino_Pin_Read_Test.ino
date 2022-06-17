int pins[] = {A0, A1, A2, A3, A4, A5, A6, A7};    //List of all Arduino Analog Pins
int pinCount = 8;                                 //Number of Pins  

void setup() {
  //For Loop to define all pins as INPUT 
  for (int i = 0; i < pinCount; i++)
  {
    pinMode(pins[i], INPUT);
  }
  pinMode(2, OUTPUT);                             //Define Pin D2 as OUTPUT to manually test any pins to HIGH
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  int valList[8] = {};                              //Create empty list of read values
  //For Loop to Read Values on the Pins
  for (int i = 0; i < pinCount; i++)
  {
    int val = 0;
    if (pins[i] == 16 || pins[i] == 17 || pins[i] == 20 || pins[i] == 21) //AnalogRead for Pins A2, A3, A6, A7 as needed on PCB
    {
      val = analogRead(pins[i]);
    }
    else                                                                //DigitalRead on remaining Pins
      val = digitalRead(pins[i]);
      
    valList[i] = val;
  }
  delay(1);
  //Loop to Print the Values
  for (int i = 0; i < pinCount; i++)
  {

    Serial.print(valList[i]);
    Serial.print("   ");
    Serial.print("   ");
  }
  Serial.println("  ");
}

//Old Function defined to manually convert Analog Values to Digital. NOT USED ANYMORE.
int analogToDigital(int pin) {
  if (analogRead(pin) < 512)
    return 0;
  else
    return 1;
}
