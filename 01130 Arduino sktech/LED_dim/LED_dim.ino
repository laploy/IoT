const int pin = 3;
const int max = 100;
const int min = 10;
const int d1 = 500;
const int d2 = 4;
int bright = 50;
bool flag = true;

void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
   if(flag)
    bright++;
  else
    bright--;
    
  if(bright > max || bright < min)
  {
    flag = !flag;
    delay(500);
  }

  analogWrite(pin, bright);
  delay(4);
}
