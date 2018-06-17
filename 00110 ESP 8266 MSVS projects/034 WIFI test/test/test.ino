/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>

#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>

const char* ssid = "xxx";
const char* password = "xxx";

void setup() 
{
	Serial.begin(9600);
	delay(300);
	Serial.println("Program started.");
}
void loop() 
{
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("Program ended.");
	while (true) { delay(100); }
}