/* Basic LED Functions 
 * 
 * Mostly just for testing
 * 
 */


 
void ledBegin(){
  pinMode(LED_BUILTIN, OUTPUT);
}


void flashBuiltIn(uint32_t delayTime = 1000, byte noLoops = 6){
  while (noLoops > 0){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delayTime);
  digitalWrite(LED_BUILTIN, LOW);
   noLoops--;
  }
}
