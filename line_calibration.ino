#include <POP32.h> //Microcontroller library please change to other INEX board

//Front IR sensors variables
const int sensorPins[4] = { 0, 1, 2, 3 };
int sensorMin[4] = { 4095, 4095, 4095, 4095 };
int sensorMax[4] = { 0, 0, 0, 0 };
int sensorAvg[4] = { 0, 0, 0, 0 };
int sensorCal[4] = { 0, 0, 0, 0 };
//----------- END ------------------//

//Sensor calibration functions
int sensor(int pin) {
  return analog(pin);
}

void cal_sensor() {
  for (int i = 0; i < 4; i++) {
    if (sensor(i) < sensorAvg[i]) { sensorCal[i] = 1; }
    if (sensor(i) > sensorAvg[i]) { sensorCal[i] = 0; }
  }
}
//----------- END ------------------//
