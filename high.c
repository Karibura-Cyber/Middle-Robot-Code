short i = 0;
short j = 0;
short a = 0;
short b = 0;
short state = 0;
short color = 0;
int l,il,ir,r,c,bl,br;

void setup()  
{
    keep_up();
    lcd("");    
}
void loop()
{   
    l = analog(0);
    il = analog(1);
    c = analog(2);
    ir = analog(3);
    r = analog(4);
    r90();
    //bk(50); sleep(100);
    ao(); sleep(1);
    track();
    if(state == 1){  
        l90();
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

void move(int x){
    fd(50); sleep(x);
}

void l90(){
    sl(100); sleep(722);
    ao(); sleep(100);
}

void r90(){
    sr(100); sleep(722);
    ao(); sleep(100);
}


void r180(){
    sr(100); sleep(722*2);
    ao(); sleep(100);
}

void l180(){
    sl(100); sleep(722*2);
    ao(); sleep(100);
}

void ss(int x){ao(); sleep(x);}

void track(){
    state = 0;
    lineup();
    
    for(j=0; j <= 150; j+=1){
        //lcd("%d",c);
        l = analog(0);
        il = analog(1);
        c = analog(2);
        ir = analog(3);
        r = analog(4);
        check();
        //if (c < 300){
        if(c < 250 || ir < 250 && il < 250){
            state = 1;
            fd(0); sleep(100);
            //bk(100); sleep(100);
            //fd(0); sleep(100);        
            break;
        }
        if (il < 250){tl(100);}
        else if (ir < 250){tr(100);}  
        else if(l < 250){tr(50);}
        else if(r < 250){tl(50);} 
        else {fd(50);}

        sleep(1);
    }
}

void check(){
    color = 0;
    if(c >= 295 && c <= 300){
        lcd("GREEN");
        ss(100);
        move(500);
        r180();
        lcd("");
        ss(10);
        
    }

}

void lineup(){
    b = 0;
    for(a = 0; a <= 25; a+=1){
        bl = analog(5);
        br = analog(7);
        if(br < 250 && bl < 250){b = 1; lcd("FIND"); ss(100); lcd(""); break;}
        else if(bl < 250){sr(50); sleep(10);}
        else if(br < 250){sl(50); sleep(10);}
        else{bk(50); sleep(1);}
    }
fd(50); sleep(10);
}
