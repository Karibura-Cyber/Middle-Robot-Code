int state = 0;
int pwl,pwr;
int l,r,enc;
#include <ipst.h>	// ATX2 Board
void setup(){
  OK();
  }
void loop(){

}

void ff(int x){motor(1,pwl); motor(2,pwr); sleep(x);}
void ss(int x){ao(); sleep(x);}
void bb(int x){motor(1,-pwl); motor(2,-pwr); sleep(x);}

void l90(){
  int x = 0;
  pwl = 18;
  pwr = 10;
  ff(0.001);
  pwl = 58;
  pwr = 50;
  while(x < 20){
    while(in(28));
    while(!in(28));
    //sl(50); sleep(1);
    motor(1,-pwl); motor(2,pwr); sleep(1);
    x++;
    if(x == 11){ao(); sleep(10); break;}
 }
  }

void r90(){
  int x = 0;
  pwl = 18;
  pwr = 10;
  ff(0.001);
  pwl = 58;
  pwr = 50;
  while(x < 20){
    while(in(28));
    while(!in(28));
    //sl(50); sleep(1);
    motor(1,pwl); motor(2,-pwr); sleep(1);
    x++;
    if(x == 11){ao(); sleep(10); break;}
 }
  }

void lineb()//for + only
{
  pwl = 28;
  pwr = 20;
 for(int i = 0; i <= 30; i++){
    while(analog(2)> 400 && analog(3)> 400) {bb(1);} //ff(24);
   if(analog(2)<= 400 && analog(3)> 400)
     {
       while(analog(3)> 400)  {motor(1,0); motor(2,-pwr); sleep(1);}
     }
   else if(analog(2)> 400 && analog(3)<= 400)
     {
       while(analog(2)> 400)  {motor(1,-pwr); motor(2,0); sleep(1);}
     }
   else if(analog(2) <= 400 && analog(3) <= 400){ao(); sleep(10000);}
  }
}

void track(){
  state = 0;
  int x = 0;
  while(x < 10){
    l = in(24);
    r = in(25);
    
    }
  }



/*
  pwl = 18;
  pwr = 10;
  bb(1);
  pwl = 28;
  pwr = 20;
  while(x < 20){
    while(in(28));
    while(!in(28));
    bb(1);
    x++;
    if(x == 20){ao(); sleep(10); break;}
    glcd(0,1,"%d",x);
 }
 */
//pwl = 58;
//pwr = 50;
