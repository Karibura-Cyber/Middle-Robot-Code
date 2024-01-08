#include <Servo.h>

Servo servo;

int servoPin = 11;
int pingPin = 13;
int inPin = 12;

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);
}

void loop() {
  long duration, cm;

  pinMode(pingPin, OUTPUT);

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  if (cm <= 10){
    Serial.println("Opened");
    servo.write(0); delay(10000);
  }
  else if (cm > 10){
    Serial.println("Closed");
    servo.write(180); delay(100);
  }
}


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
