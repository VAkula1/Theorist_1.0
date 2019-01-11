
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
    //Centreting//1-green//2-black//3-red//4-white
    int main(){
        init();
        int dopYaw;
        int inint= 0;//
        int show_my_place;//
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
            keepDeep(70);
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
        while(t.elapsed()<(3500)){
            keepDeep(90);        
            goYaw(inint);
            waitKey(1);
        }
        inint = 1000;//определение второй линии
        while(true){
            
            if (inint<1000){
                normalizeYaw(inint);
                break;}
            inint = mur.getYaw();
            keepDeep(90);
            goYaw(inint);
            inint = inint + Angle();
            waitKey(1);
                cout<<"2   "<<inint<<endl;
        }
            cout<<"2   "<<inint<<endl;
            t.stop();
            t.start();
        while(t.elapsed()<(3000)){  
            keepDeep(90);
            goYaw(inint);
            waitKey(1);
        }
        while(true){//подъезд и сброс 
            keepDeep(100);
            goYaw(inint);
            show_my_place=BasketInt();
            waitKey(1);
            if(show_my_place!=0){break;}
            }
        while(true){
            keepDeep(60);
            bool tmp = Centreting(4);
            if (tmp){
                cout<<"white centr!"<<endl;
                break;
                }    
             waitKey(1);
            }   
            
        while(true){
            bool tyaw;
            tyaw = LookYaw(inint);
            keepDeep(80);
            if(tyaw){break;}
            waitKey(1);
            }
            show_my_place=BasketInt();
            cout<<"show_my_place: "<<show_my_place<<endl;
        while(true){
            keepDeep(100);
            bool tmp = Centreting(1);
            if (tmp){
                cout<<"green centr!"<<endl;
                break;
                }    
             waitKey(1);
            }
            mur.drop();
            
            //определение места нахождения мешени
            
        while(true){
            bool tmp1 = false;
            tmp1 = Aiming(2);
            keepDeep(80);
            CW(10);
            if (tmp1){
                if (mur.getYaw()>180){x=90;}
                else{x=-90;}
                break;
                }
            waitKey(1);
            }
            cout<<"x: "<<x<<endl;
            if ((x<0&&show_my_place==-1)||(x>0&&show_my_place==1)){//переходим на темную сторону
                    while(true){
                        keepDeep(100);
                        bool tmp = Centreting(3);
                        if (tmp){
                            cout<<"red centr!"<<endl;
                            break;
                            }    
                        waitKey(1);
                        }
                }
        t.stop();//направить курс по линии 2
        t.start();
        while(t.elapsed()<(7000)){
            bool tyaw;
            tyaw = LookYaw(inint);
            keepDeep(80);
            waitKey(1);
            }
        
        t.stop();
        t.start();
        while(t.elapsed()<(1000)){
            keepDeep(90);        
            goYaw(inint-x);
            waitKey(1);
        }
        while(t.elapsed()<(2000)){
            bool tyaw;
            tyaw = LookYaw(inint);
            keepDeep(80);
            waitKey(1);
            }
        
        t.stop();
        t.start();
        while(t.elapsed()<(100)){
            keepDeep(90);        
            goYaw(inint);
            waitKey(1);
        }

        inint=1000;        //определение линии 3
        while(true){
            if (inint<1000){
                inint = normalizeYaw(inint);
                break;}
            keepDeep(110);
            inint = mur.getYaw();
            goYaw(inint);
            inint = Angle();
            waitKey(1);
                cout<<"3 "<<inint<<endl;
        }
            cout<<"3   "<<inint<<endl;
        
        t.stop();
        t.start();
        
       
        while(true){
            bool tmp = Aiming(2);
            waitKey(10);
            keepDeep(80);
            CW(10);
            if (tmp==true){
                cout<<"aiming(2)"<<endl;
                break;
                }
            waitKey(1);
            }
            
            mur.setPortA(0);
            mur.setPortB(0);
        while(true){//целим
            bool tmp=Aiming(1);
            waitKey(1);
            if (tmp)break;
                } 
            mur.shoot();
                
        t.stop();//направить курс по линии 3
        t.start();
        while(t.elapsed()<(7000)){
            bool tyaw;
            tyaw = LookYaw(inint);
            keepDeep(80);
            waitKey(1);
            }
        
        inint=1000;        //определение линии 4
        while(true){
            
            if (inint<1000){
                inint = normalizeYaw(inint+180);
                break;}
            keepDeep(110);
            inint = mur.getYaw();
            goYaw(inint);
            inint = inint + Angle();
            waitKey(1);
                cout<<"4   "<<inint<<endl;
        }
            cout<<"4   "<<inint<<endl;
        t.stop();//направить курс по линии 4
        t.start();
        while(t.elapsed()<(7000)){
            bool tyaw;
            tyaw = LookYaw(inint);
            keepDeep(80);
            waitKey(1);
            }
        //плыть по линии 4
        inint = mur.getYaw();
        while(true){
            bool tmp;
            tmp = BlackC();
            keepDeep(50);
            goYaw(inint);
            waitKey(1);
            if(tmp)break;
           
        }
            t.stop();
        while(true){//центрируемся по квадрату
            keepDeep(90);
            bool tmp = Centreting(2);
            if (tmp){
                cout<<"centr!"<<endl;
                break;
                }    
            waitKey(1);}
            mur.setPorts(0,0,-100,0);
            sleepFor(10000);
        
        return 0;
        }
    