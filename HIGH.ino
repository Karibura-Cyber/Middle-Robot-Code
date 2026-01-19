#include <POP32.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

int fl,fc,fr,bl,br;
int state = 0;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

const int BLACK_VAL = 3000;

bool isBlack(int channel) { return analog(channel) < BLACK_VAL; }

void setup() {
  waitSW_OK_bmp();
  delay(1000);
  // while (true) {
  // oled.clear();
  // oled.text(0, 0, "%d", analog(0));
  // oled.text(1, 0, "%d", analog(1));
  // oled.text(2, 0, "%d", analog(2));
  // oled.show();
  // }
  // lineup();
}

void loop()
{   
    l90();
    //bk(50); sleep(100);
    ao(); sleep(1);
    track();
    if(state == 1){  
        r90();
        track();
        if(state == 1){          
            r90();
            track();
            if(state == 1){
                r90();
                track();
            }
        }
    }
}

void ss(int x){AO(); sleep(x);}

void lineup(){
  // do {BK2(20,30);} while(analog(6))
  for (int i = 0; i < 100; i++){
    if (analog(7) < BLACK_VAL && analog(8) < BLACK_VAL){break;}
    if (analog(7) < BLACK_VAL && analog(8) > BLACK_VAL){SR(50); sleep(200); break;}
    if (analog(7) > BLACK_VAL && analog(8) < BLACK_VAL){SL(50); sleep(200); break;}
    delay(10);
  }
  AO();
  sound(1200, 100);
}

void track(){
    state = 0;

    for(int j=0; j <= 500; j+=1){
        //lcd("%d",c);
        // l = analog(0);
        // c = analog(1);
        // r = analog(2);
        // check();
        //if (c < 300){
        if(isBlack(1)){
            state = 1;
            AO(); sleep(100);
            BK2(40, 50); sleep(250);
            AO(); sleep(100);
            //bk(100); sleep(100);
            //fd(0); sleep(100);        
            break;
        }
        // if(isBlack(0)){
        //   TR(30); sleep(50);
        // }
        // else if (isBlack(2)){
        //   TL(30); sleep(50);
        // }
        // else{
        //   FD2(40,50);
        // }
    }
}
