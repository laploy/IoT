const int buttonPin = 2; 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if(digitalRead(buttonPin) == HIGH)
    Serial.print("OFF");
  else
    Serial.print("ON");
  delay(100);
}
