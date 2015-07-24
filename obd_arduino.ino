#include <Arduino.h>
#include <Wire.h>
#include <OBD.h>

COBD obd;

int myWireAddress = 5;
int otherWireAddress = 4;

int PIDs[] = {
  // Engine
  PID_RPM,
  PID_ENGINE_LOAD,
  PID_COOLANT_TEMP,
  PID_ABSOLUTE_ENGINE_LOAD,
  PID_TIMING_ADVANCE,
  PID_ENGINE_OIL_TEMP,
  PID_ENGINE_TORQUE_PERCENTAGE,
  PID_ENGINE_REF_TORQUE,
  // Intake/Exhaust
  PID_INTAKE_TEMP,
  PID_INTAKE_PRESSURE,
  PID_MAF_FLOW,
  PID_BAROMETRIC,
  // Speed/Time
  PID_SPEED,
  PID_RUNTIME,
  PID_DISTANCE,
  // Driver
  PID_THROTTLE,
  PID_AMBIENT_TEMP,
  // Electric Systems
  PID_CONTROL_MODULE_VOLTAGE
};

String commands[] = {
  "rpm",                      // Engine
  "engine_load",
  "coolant_temp",
  "abs_engine_load",
  "timing_advance",
  "engine_oil_temp",
  "engine_torque_percentage",
  "engine_ref_torque",
  "intake_temp",              // Intake/Exhaust
  "intake_pressure",
  "maf_flow",
  "barometric",
  "speed",                    // Speed/Time
  "runtime",
  "distance",
  "throttle",                 // Driver
  "ambient_temp",
  "control_module_voltage"    // Electric Systems
};

int _result = 0;

void setup() {
  Wire.begin(myWireAddress);
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
  String cmd_str(cmd_char);
  
  int calledCommand;
  bool found = false;
  for (int i = 0; i < sizeof(commands); i++) {
    if (cmd_str == commands[i]) {
      calledCommand = i;
      found = true;
      break;
    }
  }
  if (found) {
    if (obd.read(PIDs[calledCommand], _result)) {
      return;
    }
  }
  _result = 0;
}

void readOBD() {
  Wire.write(_result);
}