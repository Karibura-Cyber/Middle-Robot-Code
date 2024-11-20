// #include <POP32.h>
#include <popx2.h>
#include <NH8CHIR.h>

int sensorValues[8];
int threshold = 2000;

// PID constants
float Kp = 6.15;
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
  servo(2, 30); delay(500);
  sound(1200, 100); delay(20);
  sound(1200, 100); delay(20);
  OK();
  mission();
  ao();
}

void loop() {
  // int degree = knob(0,180);
  // glcdClear();
  // glcd(0,0,"%d", degree);
  // servo(2, degree);
  // for(int i = 0; i < 8; i++){
  //   glcd(i, 0, "%d", front.read(i, SD));
  // }
}