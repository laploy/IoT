#define TRIGGER_PIN  D1
#define ECHO_PIN     D2

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");

  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);
}


