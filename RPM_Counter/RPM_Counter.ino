#include <SPI.h>

// read RPM
long half_revolutions = 0;
long rpm = 0;
unsigned long lastmillis = 0;
void setup() {
  //pinMode(A0, INPUT_PULLUP);

  Serial.begin(115200);

  attachInterrupt(A0, rpm_fan, FALLING);

  //pinMode(A0, OUTPUT);
}
byte delaytime = 2;
void loop() {
  unsigned long millisnow = millis();
  if (millisnow - lastmillis >= 1000) { //Uptade every one second, this will be equal to reading frecuency (Hz).
    detachInterrupt(0);//Disable interrupt when calculating
    rpm = half_revolutions * 30; // Convert frequency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
    Serial.print("RPM =\t"); //print the word "RPM" and tab.
    Serial.print(rpm); // print the rpm value.
    Serial.print("\t Hz=\t"); //print the word "Hz".
    Serial.println(half_revolutions); //print revolutions per second or Hz.

    half_revolutions = 0; // Restart the RPM counter
    lastmillis = millis(); // Update lasmillis
    attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
    //blinkalot();
  }
}
// this code will be executed every time the interrupt 0 (pin2) gets low.
void rpm_fan() {
  half_revolutions++;
}
