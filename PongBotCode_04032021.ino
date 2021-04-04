const int transistor = 2;
const int transistor2 = 3;
const int pingPin = 7;
char inputByte;
long cm1;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode (13,OUTPUT);
  pinMode (transistor2, OUTPUT);
  pinMode (transistor, OUTPUT);
  Serial.begin(9600);
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
  Serial.print("cm1");
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
