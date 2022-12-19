#include <ATX2.h>	// ATX2 Board
int L1,C1,R2,BL,BR; 
int i=1;

int PWL=55,PWR=61;  //35-39
void setup() {
 OK();
}

void loop() {
  L1 = in(24);
  C1 = in(25);
  R2 = in(26);
  BL = in(27);
  BR = in(28);

  if(C1==1)
  {
    switch (i)
    {
      case 1:rr();lineb(); break;
      case 2:rr();lineb();break;//motor(1,90);  motor(2,92); sleep(1000);break;
      case 3:ll();lineb();break;
      case 4:ll();lineb();break;
      case 5:rr();lineb();break;
      case 6:ss(10000);break;
    }
    i++;
  }
  else if(L1==1)  {motor(2,55); motor(2,30); sleep(200);} //40,20
  else if(R2==1)  {motor(1,30); motor(2,55); sleep(200);} //20,40
  
  else ff(10);
}
void ff(int x) { motor(1,PWL);  motor(2,PWR); sleep(x); }
void bb(int x) { motor(1,-PWL); motor(2,-PWR); sleep(x); }
void ss(int x) { fd(0);sleep(x);  }
void rr() {ss(500); bb(100); motor(1,35); motor(2,-35);sleep(450);ss(200);}
void ll() {ss(500); bb(100); motor(1,-35); motor(2,35);sleep(450);ss(200);}


void lineb()//for + only
{
 while(in(27)==0 && in(28)==0) {bb(1);} //ff(24);
 if(in(27)==1 && in(28)==0)
   {
     while(in(27)==0)  {motor(1,0);motor(2,-15);sleep(1);}
   }
 else if(in(27)==0 && in(28)==1)
   {
     while(in(27)==0)  {motor(1,-15);motor(2,0);sleep(1);}
   }
}
