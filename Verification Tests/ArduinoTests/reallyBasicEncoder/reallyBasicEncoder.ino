#define ENCESQ 2
#define ENCDIR 3

long PULSOESQ = 0;
long PULSODIR = 0;

void encoderesq()
{
  PULSOESQ++;
}

void encoderdir()
{
  PULSODIR++;
}

void setup()
{
  Serial.begin( 9600 );
  while ( !Serial );
  Serial.println( "Pin Interrupt Demo" );

  pinMode( ENCESQ, INPUT_PULLUP );
  pinMode( ENCDIR, INPUT_PULLUP );

  //digitalWrite(ENCESQ, HIGH); //turn pullup resistor on

  attachInterrupt( EXTERNAL_INT_2 , encoderesq, CHANGE );
  attachInterrupt( digitalPinToInterrupt( ENCDIR ), encoderdir, CHANGE );

}

void loop()
{

  Serial.print( "PULSOESQ: " );
  Serial.println( PULSOESQ );

  Serial.print( "PULSODIR: " );
  Serial.println( PULSODIR );

  delay( 1000 );
}
