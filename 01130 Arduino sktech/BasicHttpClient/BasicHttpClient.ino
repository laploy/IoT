#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
const char* ssid = "XXX";
const char* password = "XXX";

void setup() {
  USE_SERIAL.begin(115200);
  USE_SERIAL.printf("\n");
  USE_SERIAL.printf("Connecting to %s\n", ssid);
  WiFiMulti.addAP(ssid, password);
  while (WiFiMulti.run() != WL_CONNECTED) 
  {
    delay(100);
    USE_SERIAL.printf(".");
  }
  USE_SERIAL.printf("\n");
  USE_SERIAL.printf("WiFi connected");
}

void loop() {
  HTTPClient http;
  USE_SERIAL.print("[HTTP] begin...\n");
  yield();
  http.begin("http://www.newslookup.com/rss/wires/newslookup-wires.rss"); 
  yield();
  USE_SERIAL.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  yield();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      yield();
      String payload = http.getString();
      yield();
      USE_SERIAL.println(payload);
    }
  } else {
    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  yield();
  delay(3000);
}

