int Led=BUILTIN_LED;

int mic =D1;
int val;
void setup()
{
    pinMode(Led,OUTPUT);
    pinMode(mic,INPUT);
}
void loop()
{
    val=digitalRead(mic);
    if(val==HIGH)
    {
        digitalWrite(Led,HIGH);
    }
    else
    {
        digitalWrite(Led,LOW);
    }
}



