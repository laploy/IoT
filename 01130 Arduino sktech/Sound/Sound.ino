int sensorPin = A0; 
int ledPin =BUILTIN_LED; 
int sensorValue = 4; 
 
void setup () 
{
  pinMode (ledPin, OUTPUT);
  Serial.begin (9600);
}
 
void loop () 
{
  sensorValue = analogRead (sensorPin);
  Serial.println (sensorValue, DEC);
  digitalWrite (ledPin, HIGH);
  delay (sensorValue);
  digitalWrite (ledPin, LOW);
  delay (sensorValue);
}







