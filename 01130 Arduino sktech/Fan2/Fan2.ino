int InA = D1;
int InB = D2;
void setup() {
   pinMode(InA,OUTPUT);
   pinMode(InB,OUTPUT);
   digitalWrite(InA,LOW);
   digitalWrite(InB,LOW);
   digitalWrite(InA,HIGH);
   delay(10);
   analogWrite(InA,150);
  }

void loop() {
}


