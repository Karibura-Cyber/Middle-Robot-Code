#include <ipst.h>
#include  <gp2d120.h>
int lo,ln,ro,rn;
int lineV = 0;
int groundV = 0;
int meanV = 500;
int N = 5;
int motorSpeed;
int baseSpeed = 90;
int rightSpeed,leftSpeed;
int maxSpeed = 100;
int sum_error = 0;
// PID
int error = 0;
int pre_error = 0;
int Kp = 30;
int Kd = 25;
int Ki = 0;
int i = 1;

bool B(int n){  
  if(n < meanV){
    return true;
  }
  else{
    return false;
  }
}

bool W(int n){  
  if(n >= meanV){
    return true;
  }
  else{
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
    //All white
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
   pre_error = error;
   sum_error += error;
}

void do_case(){
  switch(i){
    case 1: ao(); sleep(1000); servo(1,90); delay(500); fd(50); sleep(2000); break;
    case 2: ao(); sleep(10000);
    }
    i++;
  }


void setup() {
  servo_set();
  glcd(0,0,"Ready");
  glcd(4,0,"SPD: %d", maxSpeed);
  glcd(5,0,"KP: %d", Kp);
  glcd(6,0,"KD: %d", Kd);
  while(!in(16));
  while(in(16));
  /*for(int x = 0; x <= 3; x++){
    glcdClear();
    setTextSize(10);
    glcd(0,0,"%d",3-x);
    delay(1000);
  }*/
  //servo(1,90); delay(500);
  glcdClear();

}

void loop() {
  /*
  if( B(analog(0)) && B(analog(1)) && B(analog(2)) && B(analog(3)) && B(analog(4)) || B(analog(0)) && B(analog(1)) && B(analog(2)) || B(analog(3)) && B(analog(4)) && B(analog(2)) || B(analog(2)) && B(analog(0)) && B(analog(4))){
    do_case();
  }
  else{
    Tl();
  }*/

  Tl();
}

void ff(int spd, int x){fd(spd); sleep(x);}
void bb(int spd, int x){bk(spd); sleep(x);}
void ss(int x){ao(); sleep(x);}


void sensor_check(){
  glcd(0,1,"L: %d", analog(0));
  glcd(1,1,"L1: %d", analog(1));
  glcd(2,1,"C: %d", analog(2));
  glcd(3,1,"R1: %d", analog(3));
  glcd(4,1,"R: %d", analog(4));
  }


void servo_set(){
  servo(1,0); delay(500);
  servo(2,80); delay(500);
  }


void l90()
{
 ss(100);
 while(W(analog(5)) && W(analog(6))) {ff(50, 1);}
 ss(100);
 sl(100); sleep(375);
 ss(100);
}

void r90()
{
 ss(100);
 while(W(analog(5)) && W(analog(6))) {ff(50, 1);}
 ss(100);
 sr(100); sleep(375);
 ss(100);
}

void l180(){
 ss(100);
 while(W(analog(5)) && W(analog(6))) {ff(50, 1);}
 ss(100);
 sl(100); sleep(750);
 ss(100); 
}

void r180(){
 ss(100);
 while(W(analog(5)) && W(analog(6))) {ff(50, 1);}
 ss(100);
 sr(100); sleep(750);
 ss(100); 
}

void obb()//for + only
{
 while(W(analog(5)) && W(analog(6))) {bb(25, 1);} //ff(24);
 if(B(analog(5)) && W(analog(6)))
   {
     while(W(analog(6)))  {motor(1,0);motor(2,-30);sleep(1);}
   }
 else if(W(analog(5)) && B(analog(6)))
   {
     while(W(analog(5)))  {motor(1,-30);motor(2,0);sleep(1);}
   }
}
