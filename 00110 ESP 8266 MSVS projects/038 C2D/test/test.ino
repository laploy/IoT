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
	pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
	Serial.begin(9600);
	setup_wifi();
	client.setServer(mqtt_server, 8883);
	client.setCallback(callback);
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
void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
	// Switch on the LED if an 1 was received as first character
	if ((char)payload[0] == '1')
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
	else 
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
}
void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(deviceId, hubUser, hubPass)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish(outTopic, "hello world");
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
}