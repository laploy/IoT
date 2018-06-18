const int ledPin = 9;

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String s = Serial.readString();
    int x = s.toInt();
    byte volts = (byte)x;
    Serial.print(s);
    analogWrite(ledPin, volts);
  }
}
