const int transistor = 2;
const int transistor2 = 3;
const int pingPin = 7;
char inputByte;
long cm1;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode (13,OUTPUT);
  pinMode (transistor2, OUTPUT);
  pinMode (transistor, OUTPUT);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
}
}
void loop() {
  while(Serial.available()>0){
  inputByte= Serial.read();
  Serial.println(inputByte);
  
  if (inputByte=='1'){
  digitalWrite(13,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  int x;
  x = laserPing();
  JugPower(x);
  getRPM();
  digitalWrite(LED_BUILTIN,LOW);
  }
  
  else if (inputByte=='0'){
    digitalWrite(13,LOW);
    laserPing();
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
  } 
  else if (inputByte=='2'){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
  } 
  }
}

int laserPing(){
  long duration;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
 
  cm1 = duration / 29 / 2;
  //cm1 = microsecondsToCentimeters(duration);
  Serial.print(cm1);
  Serial.print("cm's away");
  Serial.println();
  delay(100);
  return cm1;
}

int JugPower(int x){
  
  digitalWrite (transistor, HIGH);
  digitalWrite (transistor2, HIGH);
  delay(4000);
  digitalWrite (transistor, LOW);
  digitalWrite (transistor2, LOW);
  delay(500);

}

int getRPM(){
    // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  //Serial.println(average);
  Serial.println(average);
  delay(1); 
  //freq=freq_read(pin);
}

long getFrequency(int pin) {
#define SAMPLES 4096
long freq = 0;
for(unsigned int j=0; j<SAMPLES; j++) freq+= 500000/pulseIn(pin, HIGH, 250000);
freq = freq / SAMPLES;
  Serial.print(freq);
  Serial.print("frequency");
  Serial.println();

}
