//PWM: 3, 5, 6, 9, 10, and 11. 
const int ledPin = 5;      // the pin that the LED is attached to

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  analogWrite(ledPin, 10);
  delay(500);
  analogWrite(ledPin, 120);
  delay(500);
  analogWrite(ledPin, 255);
  delay(500);
}


