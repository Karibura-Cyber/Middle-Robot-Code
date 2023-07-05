#include <ATX2.h> // ATX2 Board
int L1,C1,C2,R2,BL,BR;
int i = 1;

void setup()
{
  OK();
}

void loop()
{
  L1 = in(24);
  C1 = in(25);
  C2 = in(26);
  R2 = in(27);
  BL = in(28);
  BR = in(29);
  if (C1==1 && C2==1 || L1== 1 && C1==1 || C2==1 && R2==1 || L1==1 && R2==1)
  {
    switch (i)
    {
    case 1:sbr();ll();lineb(); break;
    case 2:sbr(); ss(10000); break;
    }
    i++;
  }
  else if (L1 == 1){motor(1, 50); motor(2, 0);}
  else if (R2 == 1){motor(1, 0); motor(2, 50);}

  else ff(10);
}
void ff(int x) {motor(1,50); motor(2,50); sleep(x);}
void ss(int x) {motor(1,0); motor(2,0); sleep(x);}
void bb(int x) {motor(1,-50); motor(2,-50); sleep(x);}

void sbr() {ss(50); bb(450); ss(500);}

void rr() {motor(1,50); motor(2,-50);sleep(600);ss(200);}
void ll() {motor(1,-50); motor(2,50);sleep(600);ss(200);}


void lineb()//for + only
{
 while(in(28)==0 && in(29)==0) {bb(1);} //ff(24);
 if(in(28)==1 && in(29)==0)
   {
     while(in(28)==0)  {motor(1,0);motor(2,-25);sleep(1);}
   }
 else if(in(28)==0 && in(29)==1)
   {
     while(in(28)==0)  {motor(1,-25);motor(2,0);sleep(1);}
   }
}