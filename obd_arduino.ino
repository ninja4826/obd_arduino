#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <OBD.h>

COBD obd;
StaticJsonBuffer<200> jsonBuffer;
JsonObject& root;
void setup() {
  Wire.begin(5);
  obd.begin();
  while (!obd.init());
  Wire.onRequest(sendJSON);
  root = jsonBuffer.createObject();
}

void loop() {
  delay(100);
}

void sendJSON() {
  // JsonObject& root = jsonBuffer.createObject();
  
  int value;
  if (obd.read(PID_RPM, value)) {
    root["rpm"] = value;
  }
//  read from OBD into root
//  print back to wire.
}

void readOBD(JsonObject &root) {
  
}