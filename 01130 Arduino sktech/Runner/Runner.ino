const int pins[] = {2,3,4};
const int timer = 100;

void setup() {
  for(int i = 0; i <= 2; i++)
    pinMode(pins[i], OUTPUT);
}

void loop() {
  for(int i = 0; i <= 2; i++)
  {
    digitalWrite(pins[i], HIGH);
    delay(timer);
    digitalWrite(pins[i], LOW);
    delay(timer);
  }
}
