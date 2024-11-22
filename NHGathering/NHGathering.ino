// #include <POP32.h>
#include <popx2.h>
#include <NH8CHIR.h>

int sensorValues[8];
int threshold = 2200;

// PID constants
float Kp = 6.5;
float Ki = 0;
float Kd = 1.1;

// PID variables
int error = 0;
int lastError = 0;
float integral = 0;
float derivative = 0;
int baseSpeed = 80;

NH8CHIR front(0x4B);

void setup() {
  // Serial.begin(115200);
  front.init();
  upFull();
  bigKeep();
  sound(1200, 100); delay(20);
  sound(1200, 100); delay(20);
  OK();
  mission();
  ao();
}

void loop() {
  servoConfig();
}