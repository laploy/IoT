int pins[] = {2,3,4};

void setup() {
  for(int i = 0; i <= 2; i++)
    pinMode(pins[i], OUTPUT);
}

void loop() {
  for(int i = 0; i <= 2; i++)
    digitalWrite(pins[i], HIGH);
  delay(1000);
  for(int i = 0; i <= 2; i++)
    digitalWrite(pins[i], LOW);
  delay(1000);
}
