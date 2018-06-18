const int line = 30;

void setup() {
  Serial.begin(9600);
  Serial.println("Program Start!");
}

void loop() {
  char c;
  for(c = 33; c < 126; c++)
  {
    Serial.print(c);
    delay(100);
    if(c%line == 0) Serial.println();
  }
  Serial.println();
  Serial.println("----------");
}
