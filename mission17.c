int l,r,l1,r1,bl,br,c;
int i = 1;
int a = 0;
void setup()  
{
    lcd("");
}
void loop()
{
    l = analog(0);
    l1 = analog(1);
    r1 = analog(3);
    r = analog(4);
    bl = analog(5);
    br = analog(7);
    c = analog(8);
    

    if(l < 512 && l1 < 512 || r < 512 && r1 < 512 || l < 512 && r < 512){
        switch(i){
            case 1: ff(100); break;
            case 2: check_ball(); break;
            
            
        }
        i++; sleep(200);
    }
    else if(l < 512){
        motor(1, 40); motor(2, 80);
    }
    else if(r < 512){
        motor(1, 80); motor(2, 40);
    }
    else if(r1 < 512){
        tr(80);
    }
    else if(l1 < 512){
        tl(80);
    }
    else{
        ff(100);
    }
}

void ff(int x){fd(100); sleep(x);}
void bb(int x){bk(100); sleep(x);}
void ss(int x){fd(0); sleep(x);}

void l90()
{
 ss(100);
 ff(380);
 sl(100); sleep(690);
 ss(100);
}

void r90()
{
 ss(100);
 ff(380);
 sr(100); sleep(690);
 ss(100);
}

void l180()
{
 ss(100);
 ff(380);
 sl(100); sleep(690*2);
 ss(100);
}

void r180(){
 ss(100);
 ff(380);
 sr(100); sleep(690*2);
 ss(100);
}

void ll180()
{
 sl(100); sleep(690*2);
 ss(100);
}

void rr180(){
 sr(100); sleep(690*2);
 ss(100);
}
void down(){
    keep_down();
    ff(500);
    bb(500);
}
void check_ball() {
    c = 0;
    while (c==0){
        c = analog(8);
        //lcd("C= %d",c);
        if(c>0){break;}
        else fd(100); sleep(10);
    }
    if(c < 1000){
        //lcd("BLACK!!");
        to_black();
    }
    else if(c > 1000){        
        //lcd("WHITE!!");
        to_white();
    }
    
}

void to_black(){
    keep_up();
    ff(200);
    r90();
    int i = 1;
    
    while (true) {
        
        l = analog(0);
        l1 = analog(1);
        r1 = analog(3);
        r = analog(4);
        //lcd("%d", i);
        //lcd("%d", a);
        if(l < 512 && l1 < 512 || r < 512 && r1 < 512 || l < 512 && r < 512){
        switch(i){
            case 1: down(); bb(100); rr180(); a++; break;
            case 2: r90(); check_ball(); break;
                 
        }
        i++; sleep(200);
        }
        else if(l < 512){
            motor(1, 40); motor(2, 80);
        }
        else if(r < 512){
            motor(1, 80); motor(2, 40);
        }
        else if(r1 < 512){
            tr(80);
        }
        else if(l1 < 512){
            tl(80);
        }
        else{
            ff(100);
        }
        if(a == 4){break;}
    }
    back_black();
}

void to_white(){
    keep_up();
    ff(200);
    l90();
    int i = 1;
    
    while (true) {
        
        l = analog(0);
        l1 = analog(1);
        r1 = analog(3);
        r = analog(4);
        //lcd("%d", a);
        if(l < 512 && l1 < 512 || r < 512 && r1 < 512 || l < 512 && r < 512){
        switch(i){
            case 1: down(); bb(100); rr180(); a++;break;
            case 2: l90(); check_ball(); break;
            
            
                 
        }
        i++; sleep(200);
        }
        else if(l < 512){
            motor(1, 40); motor(2, 80);
        }
        else if(r < 512){
            motor(1, 80); motor(2, 40);
        }
        else if(r1 < 512){
            tr(80);
        }
        else if(l1 < 512){
            tl(80);
        }
        else{
            ff(100);
        }
        if(a == 4){break;}
    }
    back_white();
}

void back_black(){
    int i = 1;
    lcd("BACK TO HOME!");
    while (true){
        l = analog(0);
        l1 = analog(1);
        r1 = analog(3);
        r = analog(4);
        //lcd("%d", a);
        if(l < 512 && l1 < 512 || r < 512 && r1 < 512 || l < 512 && r < 512){
        switch(i){
            case 1: l90(); break;
            case 2: ff(100); break;
            case 3: ff(100); break;
            case 4: ff(100); break;
            case 5: ff(1000); ss(10000); break;
                 
        }
        i++; sleep(200);
        }
        else if(l < 512){
            motor(1, 40); motor(2, 80);
        }
        else if(r < 512){
            motor(1, 80); motor(2, 40);
        }
        else if(r1 < 512){
            tr(80);
        }
        else if(l1 < 512){
            tl(80);
        }
        else{
            ff(100);
        }
    }
        
}
    
void back_white(){
    int i = 1;
    lcd("BACK TO HOME!");
    while (true){
        l = analog(0);
        l1 = analog(1);
        r1 = analog(3);
        r = analog(4);
        //lcd("%d", a);
        if(l < 512 && l1 < 512 || r < 512 && r1 < 512 || l < 512 && r < 512){
        switch(i){
            case 1: r90(); break;
            case 2: ff(100); break;
            case 3: ff(100); break;
            case 4: ff(100); break;
            case 5: ff(500); ss(10000); break;
                 
        }
        i++; sleep(200);
        }
        else if(l < 512){
            motor(1, 40); motor(2, 80);
        }
        else if(r < 512){
            motor(1, 80); motor(2, 40);
        }
        else if(r1 < 512){
            tr(80);
        }
        else if(l1 < 512){
            tl(80);
        }
        else{
            ff(100);
        }
    }
        
}
