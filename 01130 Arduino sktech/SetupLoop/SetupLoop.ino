  int i;

void setup() {
  i = 1;
  Serial.begin(9600);
}

void loop() {
  i++;
  Serial.print(i);
  if(i > 10) i =1;
  delay(1000);
}
