#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_PIN 2

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin(); 
}

void loop() {
  sensors.requestTemperatures(); 
  Serial.print(sensors.getTempCByIndex(0)); 
  delay(1000);
}
