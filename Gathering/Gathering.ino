#include <ipst.h>	// ATX2 Board
#include <gp2d120.h>
//int[] sensorsValue = new int[5]; // do not use 0 index
int lo,ln,ro,rn;
int lineV = 0;
int groundV = 0;
int meanV = 500;
int N = 5;
int motorSpeed;
int baseSpeed = 65;
int rightSpeed,leftSpeed;
int maxSpeed = 65;
int sum_error = 0;

// PID
int error = 0;
int pre_error = 0;
int Kp = 15;
int Kd = 0;
int Ki = 0;

bool B(int n){  
  if(n < meanV){ // is black
      return true;
  }else{
      return false;
  } 
}

bool W(int n){  
    if(n >= meanV){ // is white
      return true;
  }else{
      return false;
  } 
}

void Tl(){

    if( W(analog(0)) && W(analog(1)) && W(analog(2)) && W(analog(3)) && B(analog(4)) ){ 
        error = 4;
    }else if( W(analog(0)) && W(analog(1)) && W(analog(2)) && B(analog(3)) && B(analog(4)) ){
      error = 3;
    }else if( W(analog(0)) && W(analog(1)) && W(analog(2)) && B(analog(3)) && W(analog(4)) ){
      error = 2;
    }else if( W(analog(0)) && W(analog(1)) && B(analog(2)) && B(analog(3)) && W(analog(4)) ){
      error = 1;
    }else if( W(analog(0)) && W(analog(1)) && B(analog(2)) && W(analog(3)) && W(analog(4)) ){
      error = 0;
    }else if( W(analog(0)) && B(analog(1)) && B(analog(2)) && W(analog(3)) && W(analog(4)) ){
      error = -1;
    }else if( W(analog(0)) && B(analog(1)) && W(analog(2)) && W(analog(3)) && W(analog(4)) ){
      error = -2;
    }else if( B(analog(0)) && B(analog(1)) && W(analog(2)) && W(analog(3)) && W(analog(4)) ){
      error = -3;
    }else if( B(analog(0)) && W(analog(1)) && W(analog(2)) && W(analog(3)) && W(analog(4)) ){
        error = -4;
    }
    /// check WWWWW
    else if( W(analog(0)) && W(analog(1)) && W(analog(2)) && W(analog(3)) && W(analog(4)) ){
        error = pre_error;
    }


   
   motorSpeed = Kp*error + Kd*(error - pre_error) + Ki*(sum_error);
   leftSpeed = baseSpeed + motorSpeed;
   rightSpeed = baseSpeed - motorSpeed;
   
   if(leftSpeed > maxSpeed) leftSpeed = maxSpeed;
   if(rightSpeed > maxSpeed) rightSpeed = maxSpeed;

   if(leftSpeed < -maxSpeed) leftSpeed = -maxSpeed;
   if(rightSpeed < -maxSpeed) rightSpeed = -maxSpeed;
   
   motor(1,leftSpeed);
   motor(2,rightSpeed);
   sleep(33);  
   //glcd(0,0,"ML: %d", leftSpeed); 
   //glcd(1,0,"MR: %d", rightSpeed);
   pre_error = error;
   sum_error += error;
   
   
}
void setup() {
  servo_set();
  //OK();
  while(!in(16));
  while(in(16));
  /*for(int x = 0; x <= 3; x++){
    glcdClear();
    setTextSize(10);
    glcd(0,0,"%d",3-x);
    delay(1000);
  }*/
  glcdClear();

}

void loop() {
Tl();
//glcd(0,0, "DIST : %d", getdist(20));
}
void servo_set(){
   servo(2,0); delay(350);
   servo(1,0); delay(1000);
  }
