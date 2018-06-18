int i;

void setup() {
  i = 1;
  Serial.begin(9600);
  Serial.println("Program Start!");
}

void loop() {
  Serial.println(i++);
  if(i > 10)
  {
    Serial.print("Done.");
    while(true) {}
  }
  delay(1000);
}
