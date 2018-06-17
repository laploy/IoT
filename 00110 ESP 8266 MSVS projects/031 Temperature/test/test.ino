/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>

#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS  D4  // DS18B20 pin D4

OneWire myWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&myWire);

void setup() {
	Serial.begin(9600);
	pinMode(16, OUTPUT);
	delay(300);
	Serial.println("Program started.");
}
void loop() {
	Serial.println(getTemperature());
	blink();
}
float getTemperature() {
	float temp;
	do {
		DS18B20.requestTemperatures();
		temp = DS18B20.getTempCByIndex(0);
		delay(100);
	} while (temp == 85.0 || temp == (-127.0));
	return temp;
}
void blink()
{
	digitalWrite(16, HIGH);
	delay(50);
	digitalWrite(16, LOW);
	delay(300);
}