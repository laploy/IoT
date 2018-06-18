const int pin = 3;

void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(pin, HIGH);
    delay(180);
    digitalWrite(pin, LOW);
    delay(80);
  }
  delay(5000);
}
