/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>

int i;

void setup() {
	Serial.begin(9600);
	pinMode(16, OUTPUT);
}

void loop() {
	Serial.print("Hello, World! ");
	Serial.println(i++);
	if (i > 250) i = 0;
	digitalWrite(16, HIGH);
	delay(50);
	digitalWrite(16, LOW);
	delay(300);
}








