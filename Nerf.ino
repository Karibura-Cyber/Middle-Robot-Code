#include <ipst.h>
#include <gp2d120.h>

int L1,L2,R1,R2,C1,C2;
int i=1;

int PWL=73,PWR=80;//72 80
  //PWL=23,PWR=25;  //push can
  //PWL=40,PWR=43;
  //PWL=37,PWR=40;
//bb150 can , find new case bb200 , kick can 23,25/40,43
//0=no while,1=orginal,2=ss,3=sb  
//custom can  :  tr(30);sleep(120);fd(25);sleep(190);jub();  bw();  ff(250);lx90(0);
void setup() 
{
  servoset();
  //PWL=40,PWR=43;
  
  OK();delay(300); 
}
 
void loop() 
{
  //ff(2000);ss(9000);

  
  L2 = in(24);
  L1 = in(25);
  R1 = in(26);
  R2 = in(27);
  
  C1 = in(28);
  C2 = in(29);
  
  if(L2==1 && R2==1 || L2==1 && L1==1 || R2==1 && R1==1)
  {
   switch (i)
    {
     
     //case 1:l(1);i=0;break;
     //case 1:line();ss(9000);break;
     //case 1:ss(99999);break;
     //case 1:wangl();ss(9999);break;
     
     //case 1:ff(100);break;
     
     
     
     
       
     
     
     
     
     
         
     
      
     
     
     
     
     
     
     
     
       
    
    
        
     
     


     
     
    }
    i++;
  }
  
  else if(L2==1)    {motor(1,20);  motor(2,82);  sleep(10);} //20 82
  else if(R2==1)    {motor(1,80);  motor(2,23);  sleep(10);} //80 23
 
  else if(L1==1)  {motor(1,41);  motor(2,82);  sleep(10);} //41 82
  else if(R1==1)  {motor(1,80);  motor(2,44);  sleep(10);} //80 44
   
  else ff(10);
  
}

void ss(int x)  {  fd(0);sleep(x);  }
void ff(int x)  {  motor(1,PWL);   motor(2,PWR);   sleep(x);  }
void bb(int x)  {  motor(1,-PWL);  motor(2,-PWR);  sleep(x);  }

void servoset()    { servo(0,105);delay(100); servo(1,94); }
void servodown()   { servo(0,12); }
void servoup()     { servo(0,105);}
void servojub()    { servo(1,37); }
void servowang()   { servo(1,94); }
void jub()         { ss(100); servodown();delay(500); servojub();delay(100); servoup();delay(100); }

void l(int x)
{
 if(x==1)      {l90();}
 else if(x==2) {l902();}
 else if(x==3) {l903();}
 else if(x==0) {l900();}
}
void r(int x)
{
 if(x==1)      {r90();}
 else if(x==2) {r902();}
 else if(x==3) {r903();}
 else if(x==0) {r900();}
}

void l90()
{
 ss(100);
 while(in(28)==0 && in(29)==0){ff(1);} ff(29);//24 //72 80
 //ss(100); 
 sl(80);sleep(140);
 //ss(100);
 while(in(25)==0)  {sl(80);sleep(1);}
 //while(in(25)==1)  {sl(80);sleep(1);}
 //while(in(26)==0)  {sl(80);sleep(1);}
 ss(100); 
}
void r90()
{
 ss(100);
 while(in(28)==0 && in(29)==0) {ff(1);} ff(22);//30
 //ss(100); 
 sr(80);sleep(140);
 //ss(100);
 while(in(26)==0)  {sr(80);sleep(1);}
 while(in(26)==1)  {sr(80);sleep(1);}
 //while(in(25)==0)  {sr(80);sleep(1);}
 ss(100); 
}
void l902()
{
 //*ss(100);*********************************
 while(in(28)==0 && in(29)==0) {ff(1);} 
 //ss(100); 
 sl(80);sleep(120);
 //ss(100);
 while(in(25)==0)  {sl(80);sleep(1);}
 while(in(25)==1)  {sl(80);sleep(1);}
 //while(in(26)==0)  {sl(80);sleep(1);}
 ss(100); 
}
void r902()
{
 //ss(100);**********************************
 while(in(28)==0 && in(29)==0) {ff(1);} 
 //ss(100); 
 sr(80);sleep(140);
 //ss(100);
 while(in(26)==0)  {sr(80);sleep(1);}
 //while(in(26)==1)  {sr(80);sleep(1);}
 //while(in(25)==0)  {sr(80);sleep(1);}
 ss(100); 
}
void l903()
{
 ss(100);
 while(in(28)==0 && in(29)==0) {ff(1);} ff(18);//20
 //ss(100); 
 sl(80);sleep(140);
 //ss(100);
 while(in(25)==0)  {sl(80);sleep(1);}
 while(in(25)==1)  {sl(80);sleep(1);}
 //while(in(26)==0)  {sl(80);sleep(1);}
 ss(100); 
}
void r903()
{
 ss(100);
 while(in(28)==0 && in(29)==0) {ff(1);} ff(18);//20
 //ss(100); 
 sr(80);sleep(140);
 //ss(100);
 while(in(26)==0)  {sr(80);sleep(1);}
 //while(in(26)==1)  {sr(80);sleep(1);}
 //while(in(25)==0)  {sr(80);sleep(1);}
 ss(100); 
}
void l900()
{
 ss(100);
 //while(in(28)==0 && in(29)==0) {ff(1);} ff(30);
 //ss(100); 
 sl(80);sleep(140);
 //ss(100);
 while(in(25)==0)  {sl(80);sleep(1);}
 while(in(25)==1)  {sl(80);sleep(1);}
 //while(in(26)==0)  {sl(80);sleep(1);}
 ss(100); 
}
void r900()
{
 ss(100);
 //while(in(28)==0 && in(29)==0) {ff(1);} ff(30);
 //ss(100); 
 sr(80);sleep(140);
 //ss(100);
 while(in(26)==0)  {sr(80);sleep(1);}
 //while(in(26)==1)  {sr(80);sleep(1);}
 //while(in(25)==0)  {sr(80);sleep(1);}
 ss(100); 
}
void track()
{
  while(getdist(30)>6)
  {
    if(in(25)==1)       {motor(1,0);  motor(2,40);  sleep(10);} //0 32
    else if(in(26)==1)  {motor(1,40);  motor(2,0);  sleep(10);} //3 20
    else ff(10);
  }
  ss(100);
  fd(25);sleep(350);
  ss(100);
}
void can()
{
 ss(100);
 servodown();delay(100);
 PWL=35,PWR=38;//POW=40; 
 track();
 servojub();delay(100);
 servoup();delay(100);
 PWL=72,PWR=80;//POW=80; 
}
void cans()//case before every cans <PWL=40,PWR=42;
{
 ss(100);
 servodown();delay(500);
 //line();
 fd(25);sleep(90);
 //PWL=23,PWR=25;
 ss(100);
 servojub();delay(100);
 servoup();delay(100);
 //while(in(28)==0 && in(29)==0) {bb(1);}
 //while(in(28)==1 || in(29)==1) {bb(1);} //bb(200);
 //line();
 ss(100);//sensor28,29อยู่หลังเส้น/sersorตัวหน้าอยู่ในช่อง=เลี้ยวแบบ90ไม่ได้
 //หลัง cans bb(60); ก็ได้
 //*  l180();
 //fd(-25);sleep(250);
 PWL=72,PWR=80;
}
void canl()//case before every cans <PWL=40,PWR=42; for stop
{
 //PWL=40,PWR=45;
 ss(100);
 sl(80);sleep(100);
 fd(25);sleep(170);
 ss(100);
 servodown();delay(500);
 servojub();delay(100);
 servoup();delay(100);
 fd(-25);sleep(170);
 sr(80);sleep(100);
 //line();
 //l180();
 //fd(-25);sleep(265);//?next l180
 PWL=72,PWR=80;
}
void canr()//case before every cans <PWL=40,PWR=42; for stop
{
 //PWL=40,PWR=45;
 ss(100);
 sr(80);sleep(95);
 fd(25);sleep(170);
 ss(100);
 servodown();delay(500);
 servojub();delay(100);
 servoup();delay(100);
 fd(-25);sleep(170);
 sl(80);sleep(95);
 //line();
 //l180();
 //fd(-25);sleep(265);//?next l180**
 PWL=72,PWR=80;
}
void wang()
{
 //while(in(28)==0 && in(29)==0) {ff(1);}
 ss(100);
 servodown();delay(500);
 servowang();delay(100);
 servoup();delay(100); 
}
void wangl()//case before every cans <PWL=40,PWR=42; for stop
{
 //ss(100);            //ss(100);
 tl(80);sleep(268);  //tl(80);sleep(290);
 ss(100);            //ss(100);
 wang();             //wang();
 tl(-80);sleep(285); //tl(-80);sleep(290); 
 //ss(100);            //ss(100);
 //bb(180);          //bb(180);
 //lx90(0);
 PWL=72,PWR=80;
}
void wangr()//case before every cans <PWL=40,PWR=42; for stop
{
 //ss(100);
 tr(80);sleep(210);
 ss(100);
 wang();
 tr(-80);sleep(270); 
 //ss(100);
 //bb(180);
 //lx90(0);
 PWL=72,PWR=80;
}
void wangs()
{
 //while(in(28)==0 && in(29)==0) {ff(1);}
 line();
 PWL=23,PWR=25;
 ss(100);
 servodown();delay(500);
 servowang();delay(100);
 servoup();delay(100);
 ff(580);
 //ss(100);**
 //PWL=72,PWR=80;
 while(in(28)==0 && in(29)==0) {bb(1);}//use lineb
 //while(in(28)==1 || in(29)==1) {bb(1);} //bb(200);
 //bb(200);line();
 //ss(100);**
 l180();
 PWL=72,PWR=80;
}
void wangsl()//low push for wang3 && for wang box
{
 //while(in(28)==0 && in(29)==0) {ff(1);}
 line();
 PWL=23,PWR=25;
 ss(100);
 servodown();delay(500);
 servowang();delay(100);
 servoup();delay(100);
 ff(400);
 //ss(100);**
 //PWL=72,PWR=80;
 while(in(28)==0 && in(29)==0) {bb(1);}//use lineb
 //while(in(28)==1 || in(29)==1) {bb(1);} //bb(200);  next180
 //ss(100);**
 l180();
 PWL=72,PWR=80;
}
void wangc()//case before first wangc if block<PWL=23,PWR=25;
{
 line();
 PWL=23,PWR=25;
 ff(850);
 bb(650);
 ss(100);
 servodown();delay(500);
 servowang();delay(100);
 servoup();delay(100);
 while(in(28)==0 && in(29)==0) {bb(1);}//use lineb
 //while(in(28)==1 || in(29)==1) {bb(1);} //bb(200);  next180
 //PWL=72,PWR=80;
 //ss(100);**
 //line();//?fix l180 at ff
 l180();
 PWL=72,PWR=80;
}
void line()//for + only
{
 PWL=23,PWR=25;
 while(in(28)==0 && in(29)==0) {ff(1);} //ff(24);
 if(in(28)==1 && in(29)==0)
   {
     while(in(29)==0)  {motor(1,0);motor(2,30);sleep(1);}
   }
 else if(in(28)==0 && in(29)==1)
   {
     while(in(28)==0)  {motor(1,30);motor(2,0);sleep(1);}
   }
 PWL=72,PWR=80;
}
void lineb()//for + only
{
 PWL=23,PWR=25;
 while(in(28)==0 && in(29)==0) {bb(1);} //ff(24);
 if(in(28)==1 && in(29)==0)
   {
     while(in(29)==0)  {motor(1,0);motor(2,-30);sleep(1);}
   }
 else if(in(28)==0 && in(29)==1)
   {
     while(in(28)==0)  {motor(1,-30);motor(2,0);sleep(1);}
   }
 PWL=72,PWR=80;
}
void bw()
{
 PWL=40,PWR=44;
 while(in(28)==0 && in(29)==0) {bb(1);}
 PWL=72,PWR=80;
}
void l180()
{
 PWL=23,PWR=25;
 ss(100);
 while(in(28)==0 && in(29)==0) {ff(1);} ff(30);
 //ss(100); 
 sl(80);sleep(140);
 //ss(100);
 while(in(25)==0)  {sl(80);sleep(1);}
 while(in(25)==1)  {sl(80);sleep(1);}
 while(in(25)==0)  {sl(80);sleep(1);}
 //while(in(25)==1)  {sl(80);sleep(1);}
 ss(100);
 PWL=72,PWR=80;
}
void r180()
{
 PWL=23,PWR=25;
 ss(100);
 while(in(28)==0 && in(29)==0) {ff(1);} ff(40);
 //ss(100); 
 sr(60);sleep(160);
 //ss(100);
 while(in(26)==0)  {sr(60);sleep(1);}
 while(in(26)==1)  {sr(60);sleep(1);}
 while(in(26)==0)  {sr(60);sleep(1);}
 ss(100);
 PWL=72,PWR=80;
}

//build
void outl()//in this case after outl rx90(3); or lx90(3);
{
 PWL=23,PWR=25;
 while(in(28)==1 || in(29)==1) {ff(1);}
 while(in(28)==0 && in(29)==0) {ff(1);}
 sl(80);sleep(270);
 line();
 //next rx90(3); or lx90(3);
}


/*     case 1:
     case 2:
     case 3:
     case 4:
     case 5:
     case 6:
     case 7:
     case 8:
     case 9:
     case 10:
     case 11:
     case 12:
     case 13:
     case 14:
     case 15:
     case 16:
     case 17:
     case 18:
     case 19:
     case 20:
     case 21:
     case 22:
     case 23:
     case 24:
     case 25:
     case 26:
     case 27:
     case 28:
     case 29:
     case 30:
     case 31:
     case 32:
     case 33:
     case 34:
     case 35:
     case 36:
     case 37:
     case 38:
     case 39:
     case 40:
     case 41:
     case 42:
     case 43:
     case 44:
     case 45:
     case 46:
     case 47:
     case 48:
     case 49:
     case 50:
     case 51:
     case 52:
     case 53:
     case 54:
     case 55:
     case 56:
     case 57:
     case 58:
     case 59:
     case 60:
     case 61:
     case 62:
     case 63:
     case 64:
     case 65: 
     case 66:
     case 67:
     case 68:
     case 69:
     case 70:
     case 71:
     case 72:
     case 73:
     case 74:
     case 75:
     case 76:
     case 77:
     case 78:
     case 79:
     case 80:
     case 81:
     case 82:
     case 83:
     case 84:
     case 85:
     case 86:
     case 87:
     case 88:
     case 89:
     case 90:
     case 91: 
     case 92:
     case 93:
     case 94:
     case 95:
     case 96:
     case 97:
     case 98:
     case 99:
     case 100:  */
