
#include <MathClass.h>
#include <Actions.h>

#include <murAPI.hpp>
#include <iostream>
#include <string>
#include <thread>

#define null 0
#define Base_Speed 30
using namespace std;
using namespace cv;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //1 - green //2 - black
    int main(){
        int inint= 0;//
        int show_me;//
        Timer t;
        t.start();
        int x = 0;// 
           
           
        int nullPos = mur.getYaw();
        while(true){
        keepDeep(90);
        
        int detected_gate = Gate();
        
        if (detected_gate<400){
            if (detected_gate<138)
                {
                CCW(3);
            }
            else if (detected_gate>185) 
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
            keepDeep(80);
            goYaw(nullPos);
        }
        while(true){//до первой линии
            keepDeep(80);
            goYaw(nullPos);
            inint = Angle();
            cout<<"1   "<<inint<<endl;
            waitKey(1);
            if (inint<360){break;}
        }
            
            t.stop();//едим до второй линии
            t.start();
        while(t.elapsed()<(3800)){
            keepDeep(90);        
            goYaw(inint);
            waitKey(1);
        }
        inint = 1000;//определение второй линии
        while(true){
            
            if (inint<360){
                normalizeYaw(inint);
                break;}
            inint = mur.getYaw();
            keepDeep(90);
            goYaw(inint);
            inint = inint + Angle();
            waitKey(1);
        }
            cout<<"2   "<<inint<<endl;
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
            
            //определение места нахождения мешени 
            
        while(true){
            bool tmp = Aiming(2);
            keepDeep(80);
            CW(10);
            if (tmp==true){break;}
            waitKey(1);
            }
        inint = mur.getYaw();
            if (inint>180){x=90;}
            else{x=-90;}
            
            t.stop();//отъезд
            t.start();
        while(t.elapsed()<(4000)){  
            keepDeep(80);
            goYaw(inint);
            waitKey(1);
        }
        while(Angle()==1000){//движение до линии 3
            keepDeep(80);
            goYaw(inint);
            waitKey(1);
            }
            //int agl3 = Angle();
            cout<<"3  "<<inint<<endl;
            mur.setPortA(0);
            mur.setPortB(0);
        while(true){//целим
            bool tmp=Aiming(1);
            waitKey(1);
            if (tmp)break;
                }  
            mur.shoot();
       inint = 1000;//определение линии 3
        while(true){
            
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
        return 0;
        }
    