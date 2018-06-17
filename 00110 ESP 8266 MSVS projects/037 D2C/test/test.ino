/// <remarks>
/// Laploy V.Angkul
/// laploy@gmail.com
/// July ,2017
/// </remarks>


#include <WiFiUdp.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "xxx";
const char* password = "xxx";
const char* mqtt_server = "xxx";
const char* deviceId = "xxx";
const char* hubUser = "xxx";
const char* hubPass = "xxx";
const char* inTopic = "devices/loydev01/messages/devicebound/#";
const char* outTopic = "devices/loydev01/messages/events/";
 
WiFiClientSecure espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
	Serial.begin(9600);
	setup_wifi();
	client.setServer(mqtt_server, 8883);
}
void setup_wifi() {
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
}
void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(deviceId, hubUser, hubPass)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish(outTopic, "d2c message");
			// ... and resubscribe
			client.subscribe(inTopic);
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}
void loop() {
	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	long now = millis();
	if (now - lastMsg > 5000) {
		lastMsg = now;
		++value;
		snprintf(msg, 25, "Test message: %i", value);
		Serial.print("Publish message: ");
		Serial.println(msg);
		client.publish(outTopic, msg);
	}
}