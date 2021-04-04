void setup()
{                
  Serial.begin(9600);
  
  pinMode(A0, INPUT_PULLUP);
  
  /* Depending on the board you're using, the interrupt declaration might have
   * a different syntax
   */
  attachInterrupt(A0, tick, RISING); 
}

long rev; //T
long prevRev = 0;
bool change = false;
int changeCount = 0;
double rpm;
double prevRPM;

void loop()                     
{
  if (change == true) {
    rev = millis();
    rpm = 60000/(rev - prevRev);
    if (rpm != prevRPM ) {
      Serial.println(String(millis()) + "~" + String(rpm));
      prevRPM = rpm;
    }
    prevRev = rev;
    change = false;
  }  
}

void tick() {
  change = true;
}
