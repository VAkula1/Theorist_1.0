

#define null 0
#define Base_Speed 30

using namespace std;
using namespace cv;

void Action2(){ 
    int inint;
//    int show_me;
    Timer t;
    t.start();
    inint = 0;
    int x = 0;    
       int nullPos = mur.getYaw();
       while(true){
        keepDeep(90);
        
        int detected_gate = Gate();
        
        if (detected_gate<400){
            if (detected_gate<138)
                {
                CCW(3);
            }
            else if (detected_gate>180) 
                {
                CW(3);
            }
            else {
                mur.setPortA(0);
                mur.setPortB(0);
                x=mur.getYaw();
                break;
            }    
        }
    }
        while(GateBool()){//к воротам
            keepDeep(80);
            goYaw(x);
            }
            t.stop();//отъезд от ворот
            t.start();
        while(t.elapsed()<(3000)){  
            keepDeep(90);
            goYaw(nullPos);
            }
        while(true){//1
            keepDeep(80);
            goYaw(nullPos);
            inint = Angle();
            cout<<"1   "<<inint<<endl;
            waitKey(1);
            if (inint<360){break;}
        }
            
            cout<<"2   "<<inint<<endl;
            
            t.stop();
            t.start();
        while(t.elapsed()<(3800)){
            keepDeep(90);        
            goYaw(inint);
            waitKey(1);
        }
        inint = 1000;
        while(true){//2
            
            if (inint<360){
                normalizeYaw(inint);
                break;}
            inint = mur.getYaw();
            keepDeep(90);
            goYaw(inint);
            inint = inint + Angle();
            waitKey(1);
        }
            cout<<"3   "<<inint<<endl;
            t.stop();
            t.start();
        while(t.elapsed()<(3000)){  
            keepDeep(90);
            goYaw(inint);
            waitKey(1);
        }
        while(BasketBool()!=true){//подъезд и сброс 
            keepDeep(110);
            goYaw(inint);
            waitKey(1);
            }
        while(true){
            keepDeep(110);
            bool tmp = Centreting(1);
            if (tmp){
                cout<<"centr!"<<endl;
                break;
                }    
             waitKey(1);
            }
            mur.drop();
            t.stop();// к последней линии
            t.start();
            while(t.elapsed()<(6000)){  
            keepDeep(90);   
            goYaw(inint);
            waitKey(1);
             }
            inint = 1000;
             while(true){//3
            if (inint<360){break;}
            keepDeep(90);
            inint = mur.getYaw();
            goYaw(inint);
            inint = Angle();
            cout<<"1   "<<inint<<endl;
            waitKey(1);
        }
            cout<<"3   "<<inint<<endl;
            t.stop();
            t.start();
        while(t.elapsed()<(6000)){ 
            keepDeep(90);
            goYaw(inint);
            waitKey(1);
        }
            t.stop();
        while(true){
            keepDeep(90);
            bool tmp = Centreting(2);
            if (tmp){
                cout<<"centr!"<<endl;
                break;
                }    
            waitKey(1);}
            mur.setPorts(0,0,-100,0);
            sleepFor(10000);
        }