
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

int inint;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //1 - green //2 - black
    int main(){ 
        while(true){
            bool tmp = Aiming();
            waitKey(1);
            tmp = Aiming();
            if (tmp){
                cout<<"centr!"<<endl;
                break;
                }
            }
    cout<<"lul"<<endl;
    mur.shoot();
//    int inint;
//    int show_me;
//    Timer t;
//    t.start();
//    inint = 0;
//    int x = 0;
        return 0;
        }