void fline(int step) {  // วิ่งตรงไปจนกว่าจะเจอเส้นตัด
  error = 0;
  readFrontSensors();
  while (1) {
    PIDControl();
    if (sensorValues[0] == 1 || sensorValues[5] == 1) {
      // sound(1200,100);
      break;
    }
  }
  fd(baseSpeed);
  sleep(step);
  ao();
}

void bbline(int channel, int step) {
  do {
    readFrontSensors();
    reverse_PIDControl();
  } while (!sensorValues[channel]);
  ss(50);
  ff(step);
  ss(1);
}

void sfline(int channel, int step) {  //เดินตรงไปจนกว่าจะเจอเส้นตัด ตามเซ็นเซอร์ที่ตั้ง 0 = ซ้ายสุด 7 = ขวาสุด
  error = 0;
  readFrontSensors();
  while (1) {
    PIDControl();
    if (sensorValues[channel]) { break; }
  }
  fd(baseSpeed);
  sleep(step);
  ao();
}
void line_sl() {  //หันซ้าย
  sl(50);
  sleep(100);
  do {
    readFrontSensors();
    sl(50);
  } while (sensorValues[0] == 0);
  do {
    readFrontSensors();
    sl(50);
  } while (sensorValues[2] == 0);
  ao();
}

void line_sr() {  //หันขวา
  sr(50);
  sleep(100);
  do {
    readFrontSensors();
    sr(50);
  } while (sensorValues[7] == 0);
  do {
    readFrontSensors();
    sr(30);
  } while (sensorValues[5] == 0);
  ao();
}

void line_sr180() {  //หมุนขวา 180 องศา **
  sr(50);
  sleep(200);
  // readFrontSensors();
  do {
    readFrontSensors();
    sr(50);
  } while (sensorValues[5] == 0);
  // do {readFrontSensors(); sr(20);} while(sensorValues[4] == 0);
  ss(10);
  // sound(1200, 100);
}

void sr_turn(int channel, int speed) {  //หมุนขวาจนกว่าเซ็นเซอร์ที่ตั้งจะเจอ
  sr(speed);
  sleep(200);
  // readFrontSensors();
  do {
    readFrontSensors();
    sr(speed);
  } while (sensorValues[channel] == 0);
  ss(50);
  // sound(1200, 100);
}

void sl_turn(int channel, int speed) {  //หมุนซ้ายจนกว่าเซ็นเซอร์ที่ตั้งจะเจอ
  sl(speed);
  sleep(200);
  // readFrontSensors();
  do {
    readFrontSensors();
    sl(speed);
  } while (sensorValues[channel] == 0);
  ss(50);
  // sound(1200, 100);
}

void sff(int step) {
  for (int i = 0; i < step; i++) {
    PIDControl();
  }
  ao();
}


void ff(int x) {
  fd(baseSpeed);
  sleep(x);
}  //วิ่งตรงตามเวลา
void bb(int x) {
  bk(baseSpeed);
  sleep(x);
}  //ถอยหลังตามเวลา
void ss(int x) {
  ao();
  sleep(x);
}  //หยุดตามเวลา


void bigKeep() { servo(2, 135); }  //คีบลูกใหญ่
void smallKeep() { servo(2, 150); }  //คีบลูกเล็ก
void unkeep() { servo(2, 30); }  //ปล่อย

void upFull(){servo(1, 180);}
void upHalf(){servo(1, 125);}
void downFull(){servo(1, 95);}

void servoConfig(){
  int deg = knob(0,180);
  // glcdClear();
  glcd(0,0, "%d", deg);
  servo(1, deg);
}