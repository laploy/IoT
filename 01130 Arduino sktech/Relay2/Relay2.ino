const int relay = 2;
const int sw = 3;
volatile int counter = 1;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(sw, INPUT);
  Serial.begin(9600);
}

void loop() {
    switch(counter)
    {
      case 1:
        Pattern1();
        break;
      case 2:
        Pattern2();
        break;
      case 3:
        Pattern3();
        break; 
      case 4:
        Pattern4();
        break; 
      case 5:
        Pattern5();
        break; 
      case 6:
        Pattern6();
        break; 
      case 7:
        Pattern7();
        break; 
    }
    if(digitalRead(sw) == LOW)
    {
      counter++;
      if(counter > 7) counter = 1;
    }

    Serial.println(counter);
    delay(100);
}

void Pattern1()
{
    digitalWrite(relay, LOW);
    delay(1000);
    digitalWrite(relay, HIGH);
    delay(50);
}

void Pattern2()
{
    digitalWrite(relay, LOW);
    delay(200);
    digitalWrite(relay, HIGH);
    delay(50);
}

void Pattern3()
{
    digitalWrite(relay, LOW);
    delay(300);
    digitalWrite(relay, HIGH);
    delay(50);
}

void Pattern4()
{
    digitalWrite(relay, LOW);
    delay(400);
    digitalWrite(relay, HIGH);
    delay(50);
}

void Pattern5()
{
    digitalWrite(relay, LOW);
    delay(500);
    digitalWrite(relay, HIGH);
    delay(50);
}

void Pattern6()
{
    digitalWrite(relay, LOW);
    delay(600);
    digitalWrite(relay, HIGH);
    delay(50);
}

void Pattern7()
{
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(relay, LOW);
    delay(200);
    digitalWrite(relay, HIGH);
    delay(50);
  }
  delay(500);
}

