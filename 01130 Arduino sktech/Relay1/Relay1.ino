const int pin = 3;

void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(pin, LOW);
    delay(300);
    digitalWrite(pin, HIGH);
    delay(1000);
  }
}
