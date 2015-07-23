#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <OBD.h>

COBD obd;

void setup() {
  Wire.begin(5);
  obd.begin();
  while (!obd.init());
  Wire.onRequest(sendJSON);
}

void loop() {
  delay(100);
}

void sendJSON() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  int value;
  if (obd.read(PID_RPM, value)) {
    root["rpm"] = value;
  }
  if (obd.read(PID_ENGINE_LOAD, value)) {
    root["engine_load"] = value;
  }
  if (obd.read(PID_COOLANT_TEMP, value)) {
    root["coolant_temp"] = value;
  }
  if (obd.read(PID_ABSOLUTE_ENGINE_LOAD, value)) {
    root["abs_engine_load"] = value;
  }
  if (obd.read(PID_TIMING_ADVANCE, value)) {
    root["timing_advance"] = value;
  }
  if (obd.read(PID_ENGINE_OIL_TEMP, value)) {
    root["engine_oil_temp"] = value;
  }
  if (obd.read(PID_ENGINE_TORQUE_PERCENTAGE, value)) {
    root["engine_torque_percentage"] = value;
  }
  if (obd.read(PID_ENGINE_REF_TORQUE, value)) {
    root["engine_ref_torque"] = value;
  }
//  read from OBD into root
//  print back to wire.
}