short i = 0;
short j = 0;
short state = 0;
short color = 0;
int l,il,ir,r,c;
void setup()  
{
    
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
    bk(100); sleep(70);
    ao(); sleep(1);
    track();
    if(state == 1){  
        l90();
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
    for(j=0; j <= 160; j+=1){
        lcd("%d",c);
        l = analog(0);
        il = analog(1);
        c = analog(2);
        ir = analog(3);
        r = analog(4);
        check();
        //if (c < 300){
        if(ir < 300 && il < 300){
            
            state = 1;
            fd(0); sleep(100);
            bk(100); sleep(70);
            //fd(0); sleep(100);        
            break;
        }
        if (il < 300){tl(100);}
        else if (ir < 300){tr(100);}  
        else if(l < 300){tr(50);}
        else if(r < 300){tl(50);} 
        else {fd(50);}

        sleep(1);
    }
}

void check(){
    color = 0;
    if(c == 473 || c == 443 || c == 301){
        lcd("GREEN");
        ss(100);
        move(300);
        r180();
        lcd("");
        ss(10);
        
    }

}
