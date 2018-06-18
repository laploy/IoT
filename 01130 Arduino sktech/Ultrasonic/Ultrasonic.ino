#include <NewPing.h>
 
#define TRIGGER_PIN  D3
#define ECHO_PIN     D2
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  delay(50);
  int uS = sonar.ping();
  Serial.print(uS / US_ROUNDTRIP_CM);
}



