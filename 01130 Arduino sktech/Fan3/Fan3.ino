int InA = D1;
int InB = D2;

void setup() {
   pinMode(InA,OUTPUT);
   pinMode(InB,OUTPUT);
   digitalWrite(InA,LOW);
   digitalWrite(InB,LOW);
   Serial.begin(9600);
   Serial.println("Ready");
  }

void loop() {
    if (Serial.available() > 0) {
    String s = Serial.readString();
    int x = s.toInt();
    byte volts = (byte)x;
    Serial.print(s);
    digitalWrite(InA,HIGH);
    delay(100);
    analogWrite(InA, volts);
  }
}



