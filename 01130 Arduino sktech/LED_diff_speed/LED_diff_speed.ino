const int red = 2;
const int yellow = 3;
const int green = 4;
const int redSpeed = 600;
const int yellowSpeed = 1200;
const int greenSpeed = 3000;
int redCount = 0;
int yellowCount = 0;
int greenCount = 0;

void setup() {
   pinMode(red,OUTPUT);
   pinMode(yellow,OUTPUT);
   pinMode(green,OUTPUT);
  }

void loop() {
  if(redCount++ > redSpeed) redCount = 0;
    if(redCount < redSpeed/2)
      digitalWrite(red, HIGH);
    else 
      digitalWrite(red, LOW);
      
  if(yellowCount++ > yellowSpeed) yellowCount = 0;
    if(yellowCount < yellowSpeed/2)
      digitalWrite(yellow, HIGH);
    else 
      digitalWrite(yellow, LOW); 

  if(greenCount++ > greenSpeed) greenCount = 0;
    if(greenCount < greenSpeed/2)
      digitalWrite(green, HIGH);
    else 
      digitalWrite(green, LOW);            
  delay(1);
}
