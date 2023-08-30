#include <ATX2.h>
#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
unsigned long timer = 0;
int pre_yaw,d_yaw;
int pitch;
void setup(){
  OK();
  glcdClear();
  Wire.begin();
  Serial.begin(9600);
  byte status = mpu.begin();
  sound(1200,100);
  sound(1200,100);
  mpu.calcOffsets();
  mpu.update();
  sound(1200,100);
  }

void loop(){
  }

void ff(int x) {FD2(40, 42); sleep(x);}
void ss(int x) {AO(); sleep(x);}

void gl90(){
  pre_yaw = mpu.getAngleZ();  
  d_yaw = pre_yaw+=78;
  ss(100);
  while(pre_yaw <= d_yaw){
    mpu.update();
    pre_yaw = mpu.getAngleZ();
    SL(50); sleep(1);
    }
    ss(100);
  }

void gr90(){
  pre_yaw = mpu.getAngleZ();  
  d_yaw = pre_yaw-=78;
  ss(100);
  while(pre_yaw >= d_yaw){
    mpu.update();
    pre_yaw = mpu.getAngleZ();
    SR(50); sleep(1);
    }
  ss(100);  
}

void track_bridge(){
  while(pitch < 5){
      mpu.update();
      pitch = mpu.getAngleY();
      //glcdClear();
      //glcd(0,0,"%d", pitch);
      FD2(15,17); sleep(1);
      //delay(100);
      }
    sound(1200,100);
    sound(1200,100);
    ss(200);
    FD2(40,42); sleep(1000);
    ss(100);
  }
