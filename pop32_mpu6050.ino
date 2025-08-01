#include "Wire.h"
#include <MPU6050_light.h>
#include <POP32.h>

MPU6050 mpu(Wire);

void gyroFD(float distance, int baseSpeed = 50);

void setup() {
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050
  mpu.calcOffsets();      // gyro and accelero
  mpu.calcOffsets();      // gyro and accelero
  sound(2000, 100);
  waitSW_A_bmp();
  delay(1000);

  //=============================================== WALL FUNCTIONS EXAMPLES ===============================
  gyroFD(20, 50);               // GYRO FORWARD 20 UNITS WITH 50% SPEED
  gyroSpin(90);                 // GYRO SPIN LEFT 90 DEGREES

  gyroFD(20, 50);               // GYRO FORWARD 20 UNITS WITH 50% SPEED
  gyroSpin(-90);                 // GYRO SPIN RIGHT 90 DEGREES
}

void loop() {
}

//GYRO SPIN LEFT AND RIGHT BY DEGREES [ POSITIVE FOR TURN LEFT | NEGATIVE FOR TURN RIGHT ]
void gyroSpin(int relative_degree) {
  int min_speed = 20;
  int max_speed = 100;
  float kp = 1.0;
  float kd = 0.1;
  float small_angle_threshold = 20.0;
  float stop_threshold = 2.0;

  float previous_error = 0;
  unsigned long lastTime = millis();

  // Read starting angle from MPU6050
  mpu.update();
  float start_angle = mpu.getAngleZ();
  float target_angle = start_angle + relative_degree;

  // Normalize target angle to [-180, 180]
  if (target_angle > 180) target_angle -= 360;
  if (target_angle < -180) target_angle += 360;

  while (true) {
    mpu.update();
    float current_angle = mpu.getAngleZ();
    float error = target_angle - current_angle;

    // Normalize error to shortest path
    if (error > 180) error -= 360;
    if (error < -180) error += 360;

    // Stop condition
    if (abs(error) <= stop_threshold) {
      motor(1, 0);
      motor(2, 0);
      break;
    }

    // Time delta for derivative
    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0;
    lastTime = now;

    float derivative = (error - previous_error) / dt;
    previous_error = error;

    // PID calculation
    float pid = kp * error + kd * derivative;

    // Soft landing logic
    int targetSpeed = constrain(abs((int)pid), min_speed, max_speed);

    if (abs(error) < small_angle_threshold) {
      targetSpeed = min_speed;  // Use minimum speed when close
    }

    // Apply motor commands
    if (pid > 0) {
      motor(1, -targetSpeed); // Turn right
      motor(2, targetSpeed);
      sl(targetSpeed);
    } else {
      motor(1, targetSpeed);  // Turn left
      motor(2, -targetSpeed);
    }

    delayMicroseconds(10);
  }
}

// FORWARD VIA GYROSCOPE WITH DISTANCE AND SPEED
void gyroFD(float distance, int baseSpeed = 50) {
  // PID gains for straight-line correction
  float Kp = 2.0;    // Proportional gain
  float Ki = 0.0;   // Integral gain
  float Kd = 0.0;  // Derivative gain

  float tolerance = 0.5;  // Angle tolerance in degrees
  int maxCorrection = 40; // Maximum speed correction
  int minSpeed = 20;      // Minimum wheel speed

  // Reset and initialize
  mpu.update();
  float initialAngle = mpu.getAngleZ();
  float currentAngle = initialAngle;
  float error = 0.0;
  float lastError = 0.0;
  float integral = 0.0;
  float derivative = 0.0;

  unsigned long lastTime = millis();
  unsigned long startTime = millis();
  unsigned long timeout = 5000; // 5 second timeout

  // Simple distance tracking (assumes constant speed and time)
  float timeToRun = (distance / baseSpeed) * 1000; // Convert to milliseconds

  while (millis() - startTime < timeToRun) {
    // Check timeout
    if (millis() - startTime > timeout) {
      ao(); // All off
      break;
    }

    mpu.update();
    unsigned long currentTime = millis();
    float dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    // Calculate angle error
    currentAngle = mpu.getAngleZ();
    error = initialAngle - currentAngle;

    // Keep error between -180 and 180
    if (error > 180.0) error -= 360.0;
    else if (error < -180.0) error += 360.0;

    // PID calculations
    float proportional = Kp * error;
    integral += Ki * error * dt;
    integral = constrain(integral, -20, 20);
    derivative = Kd * (error - lastError) / dt;
    lastError = error;

    // Calculate correction
    float correction = proportional + integral + derivative;
    correction = constrain(correction, -maxCorrection, maxCorrection);

    // Calculate wheel speeds
    int leftSpeed = baseSpeed - correction;
    int rightSpeed = baseSpeed + correction;

    // Ensure minimum speed and constrain maximum
    leftSpeed = constrain(leftSpeed, minSpeed, baseSpeed + maxCorrection);
    rightSpeed = constrain(rightSpeed, minSpeed, baseSpeed + maxCorrection);

    // Drive motors
    fd2(leftSpeed, rightSpeed);
    delay(10);
  }
  ao();
}
