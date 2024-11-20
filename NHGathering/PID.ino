
void readFrontSensors() {
  for (int i = 0; i < 8; i++) {
    int analogValue = front.read(i, SD);
    sensorValues[i] = (analogValue > threshold) ? 1 : 0;
  }
}

int calculateError(){
  int error = 0;
  if(sensorValues[0] == 1 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0){ return -7; }                // 10000000
  else if(sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return -6; }          // 11000000
  else if(sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return -5; }          // 01000000
  else if(sensorValues[0] == 0 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return -4; }          // 01100000
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 1 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return -3; }          // 00100000
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return -2; }          // 00110000
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return -1; }          // 00010000
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return 0; }           // 00011000
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 1 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return 1; }           // 00001000
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 0 && sensorValues[7] == 0) { return 2; }           // 00001100
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 1 && sensorValues[6] == 0 && sensorValues[7] == 0) { return 3; }           // 00000100
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 0) { return 4; }           // 00000110
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 1 && sensorValues[7] == 0) { return 5; }           // 00000010
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 1 && sensorValues[7] == 1) { return 6; }           // 00000011
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 1) { return 7; }           // 00000001
  else if(sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) { return lastError; }   // 00000000
  else if(sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1) { return 0; }           // 11111111
}

void PIDControl() {
  readFrontSensors();
  error = calculateError();
  integral += error;
  derivative = error - lastError;
  
  float correction = Kp * error + Ki * integral + Kd * derivative;
  
  int leftMotorSpeed = baseSpeed + correction;
  int rightMotorSpeed = baseSpeed - correction;

  fd2(leftMotorSpeed, rightMotorSpeed);
  
  lastError = error;
}

void trackLine(int step){               //จับเส้นก่อนคีบลูกบาศก์
  for(int i = 0; i < step; i++){
    readFrontSensors();
    if(sensorValues[2]){
      sl(30); sleep(20);
    }
    else if(sensorValues[5]){
      sr(30); sleep(20);
    }
    else{
      fd(30); sleep(20);
    }
  }
  ss(10);
}