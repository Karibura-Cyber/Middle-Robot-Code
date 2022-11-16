short i = 0;
short state = 0;
int l,r,il,ir,c;
void setup()  
{
}
void loop()
{
   lcd("%d",state);
   l90();
   ttrack();
    if(state == 1){
        r90();
        ttrack();
        if(state == 1){
            r90();
            ttrack();
            if(state == 1){
                l90();
                ttrack();
                if(state == 1){
                    l90();
                    ttrack();
                }
            }
        }
    }
}

void l90(){
    sl(100); sleep(680);
    ao(); sleep(100);
}

void r90(){
    sr(100); sleep(680);
    ao(); sleep(100);
}
void track(){
    state = 0;
    //bk(50); sleep(100);
    for(i = 0; i <= 130/2; i+=1){
        l = analog(0);
        il = analog(1);
        c = analog(2);
        ir = analog(3);
        r = analog(4);
        if(c < 300){
            state = 1;
            ao(); sleep(100);
            break;
        }
        else{
            if(l < 300){tr(50);}
            else if(r < 300){tl(50);}
            fd(50);
        }
        
        
        
    }
}

void ttrack(){
    state = 0;
    bk(50); sleep(50);
    ao(); sleep(1);
    i = 0;
    while(c != 300){
        i += 1; sleep(1);
        l = analog(0);
        il = analog(1);
        c = analog(2);
        ir = analog(3);
        r = analog(4);
        if(i <= 68){
            if(c < 300){
                state = 1;
                ao(); sleep(100);
                break;
                
            }
            
            if(l < 300){tr(50);}
            else if(r < 300){tl(50);}
            else if(ir < 300){tr(100);}
            else if(il < 300){tl(100);}
            else{fd(100);}
        }
        else{break;}
            
        //lcd("%d",i); sleep(1);
    }
}
