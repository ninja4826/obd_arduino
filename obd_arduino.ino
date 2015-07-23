#include <Arduino.h>
#include <Wire.h>
#include <OBD.h>

COBD obd;
int _command;
int PIDs[] = {
  PID_RPM,
  PID_ENGINE_LOAD,
  PID_COOLANT_TEMP,
  PID_ABSOLUTE_ENGINE_LOAD,
  PID_TIMING_ADVANCE,
  PID_ENGINE_OIL_TEMP,
  PID_ENGINE_TORQUE_PERCENTAGE,
  PID_ENGINE_REF_TORQUE
};
void setup() {
  Wire.begin(5);
  obd.begin();
  while (!obd.init());
  Wire.onReceive(setCommand);
  Wire.onRequest(readOBD);
}

void loop() {
  delay(100);
}

void setCommand(int numBytes) {
  char cmd_char[numBytes + 1];
  int i = 0;
  while (1 < Wire.available()) {
    cmd_char[i] = Wire.read();
    i++;
  }
  String cmd_str = str(cmd_char);
  switch (cmd_str) {
    case "rpm":
      _command = 0;
      break;
    case "engine_load":
      _command = 1;
      break;
    case "coolant_temp":
      _command = 2;
      break;
    case "abs_engine_load":
      _command = 3;
      break;
    case "timing_advance":
      _command = 4;
      break;
    case "engine_oil_temp":
      _command = 5;
      break;
    case "engine_torque_percentage":
      _command = 6;
      break;
    case "engine_ref_torque":
      _command = 7;
      break;
  }
}

void readOBD() {
  int value;
  if (obd.read(PIDs[_command], value)) {
    Wire.write(value);
  } else {
    Wire.write(0);
  }
}