#include <murAPI.hpp>

#define null 0
#define Base_Speed 30
using namespace std;
using namespace cv;

    void init(){
    int  tmp = mur.getInputAOne();
    tmp = mur.getYaw();
    //mur.initCamera(1);
    Mat img= mur.getCameraOneFrame();
    sleepFor(100);
    for (int i=0 ;i<5;i++){
        img= mur.getCameraOneFrame();  
        }
    //mur.initCamera(2);
    img= mur.getCameraTwoFrame();
    sleepFor(100);
    for (int i=0 ;i<5;i++){
        img= mur.getCameraTwoFrame();  
        }
    
}
    
    
    void keepDeep(int wish){ 
    float delta; 
    int controlD; 
    delta = wish - mur.getInputAOne(); 
    delta = delta * 8; 
    controlD = (int)delta; 
    mur.setPortC(controlD);
	sleepFor(5);
    }
    
    
int normalizeYaw(float yawToNorm){
    float yawToRet=0;
    if (yawToNorm>359)        yawToRet=yawToNorm-360;
    
    else if (yawToNorm<0)     yawToRet=360+yawToNorm;
    else yawToRet=yawToNorm;
    return yawToRet;
    
}

void CCW(int power){
  int powerA=power;
  int powerB=power*(-1);  
  mur.setPortA(powerA);
  mur.setPortB(powerB);
}

void CW(int power){
  int powerB=power;
  int powerA=power*(-1);  
  mur.setPortA(powerA);
  mur.setPortB(powerB);
}

void goYaw(int tyaw){ 
    float k = 0.50;
    int spb = 15;
    int cyaw = mur.getYaw();
    int err = tyaw-cyaw; 
    if (err<-180){ 
        err = 360-abs(err); 
    } 
    else if (err > 180){ 
        err = (360- err)*(-1); 
    } 
    int pA = spb+err*k; 
    int pB = spb-err*k; 

    mur.setPortA(pA*(-1)); 
    mur.setPortB(pB*(-1)); 
} 

int Angle(){
    Mat inPic = mur.getCameraOneFrame();
    int toRet;
   if (inPic.empty()){
      cerr<<"Image empty"<<endl;
      toRet = 1000;
   } 
   Mat red= inPic.clone();
   cvtColor(red, red, CV_BGR2HSV);
   Scalar upper_red(25,255,255);
   Scalar lower_red(0,20,0);
   
   inRange(red,lower_red,upper_red,red);
   GaussianBlur(red, red, Size(5, 5), 2);
   
   imshow("redPic",red);
   imshow("inPic",inPic);
   vector < vector <Point>> contours;
   findContours(red,contours,CV_RETR_TREE,CV_CHAIN_APPROX_NONE);
   
   
   for (size_t i=0;i<contours.size();i++){
       if (contours.at(i).size() < 5) {
            continue;
        }
       vector<Point> hull;
       convexHull(contours[i],hull,true);
       approxPolyDP(hull,hull,15,true);
        
       RotatedRect bEllipse = fitEllipse(contours.at(i));
       //Rect rect = boundingRect(contours[i]);
       //int x = (int)bEllipse.center.x;
       int y = (int)bEllipse.center.y;
       //int r = (int)rect.width/2;
       int angle =bEllipse.angle;
        
        
       if (hull.size()<8){
           putText( inPic, "angle:"+std::to_string(angle), Point(50,180), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
           putText( inPic, "hull size:"+std::to_string(hull.size()), Point(50,220), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       drawContours(inPic,contours,i,Scalar(255,0,0),4);
       }
       imshow("inPic",inPic);
       
       if (((y>110)&&(y<130))&&(hull.size()>2)){
           if(angle>90){toRet=angle+180;}
           else{toRet=angle;}
                            }
       else {toRet=1000;
               }
                 
    }
    return toRet;
}



bool BasketBool(){
    Mat inPic = mur.getCameraOneFrame();
    bool toRet;
   if (inPic.empty()){
      cerr<<"Image empty"<<endl;
      toRet=false;
   } 
   Mat green= inPic.clone();
   cvtColor(green, green, CV_BGR2HSV);
   Scalar upper_green(100,255,255);
   Scalar lower_green(42,61,95);
   
   inRange(green,lower_green,upper_green,green);
   GaussianBlur(green, green, Size(5, 5), 2);
   
   imshow("green",green);
   imshow("inPic",inPic);
   vector < vector <Point>> contours;
   findContours(green,contours,CV_RETR_TREE,CV_CHAIN_APPROX_NONE);
   
   
   for (size_t i=0;i<contours.size();i++){
       if (contours.at(i).size() < 5) {
            continue;
        }
       vector<Point> hull;
       convexHull(contours[i],hull,true);
       approxPolyDP(hull,hull,15,true);
        
    //  RotatedRect bEllipse = fitEllipse(contours.at(i));
       Rect rect = boundingRect(contours[i]);
    //   int x = (int)bEllipse.center.x;
    //   int y = (int)bEllipse.center.y;
       int r = (int)rect.width/2;
       //int angle =bEllipse.angle;
        
        
       if (hull.size()<8){
           putText( inPic, "r :"+std::to_string(r), Point(50,160), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       drawContours(inPic,contours,i,Scalar(255,0,0),4);
       }
       imshow("inPic",inPic);
       
       if (r>20){toRet=true;}
       else {toRet=false;}
               } 
       waitKey(1);   
         
       return toRet;
    }
bool GateBool(){
   Mat inPic = mur.getCameraTwoFrame();
   bool toRet;
   if (inPic.empty()){
      cerr<<"Image empty"<<endl;
      toRet=0;
   } 
   Mat green= inPic.clone();
   cvtColor(green, green, CV_BGR2HSV);
   Scalar upper_green(100,255,255);
   Scalar lower_green(42,61,95);
   
   inRange(green,lower_green,upper_green,green);
   GaussianBlur(green, green, Size(5, 5), 2);
   
   imshow("greenPic",green);
   imshow("inPic",inPic);
   vector < vector <Point>> contours;
   findContours(green,contours,CV_RETR_TREE,CV_CHAIN_APPROX_NONE);
   
   
   for (size_t i=0;i<contours.size();i++){
       if (contours.at(i).size() < 5) {
            continue;
        }
       vector<Point> hull;
       convexHull(contours[i],hull,true);
       approxPolyDP(hull,hull,15,true);
        
    //RotatedRect bEllipse = fitEllipse(contours.at(i));
       Rect rect = boundingRect(contours[i]);
    //   int x = (int)bEllipse.center.x;
    //   int y = (int)bEllipse.center.y;
       int r = (int)rect.width/2;
    //   int angle =bEllipse.angle;
        
        
       if (hull.size()<8){
           putText( inPic, "r :"+std::to_string(r), Point(50,160), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       drawContours(inPic,contours,i,Scalar(255,0,0),4);
       }
       imshow("inPic",inPic);
       
       if (r>10){toRet=true;}
       else {toRet=false;}
               } 
       waitKey(1);   
         
       return toRet;
    }        
   
bool Aiming(int mode){/////////////////////////////////////////////////
   bool toRet=false;
    Mat inPic = mur.getCameraTwoFrame();
   if (inPic.empty()){
      cerr<<"Image empty"<<endl;
      toRet=false;
   } 
   cvtColor(yellow, yellow, CV_BGR2HSV);
   int dopPowerA;
   int dopPowerB;
   int dopPowerC;
   Scalar using_upper;
   Scalar using_lower;
   Scalar upper_yellow(38,255,255);
   Scalar lower_yellow(27,217,144);
   
   using_upper=upper_yellow;
   using_lower=lower_yellow;
   
   inRange(yellow,using_lower,using_upper,yellow);
   GaussianBlur(yellow, yellow, Size(5, 5), 2);
   
   imshow("Centreting",yellow);
   vector < vector <Point>> contours;
   findContours(yellow,contours,CV_RETR_TREE,CV_CHAIN_APPROX_NONE);
   
   
   for (size_t i=0;i<contours.size();i++){
       if (contours.at(i).size() < 5) {
            continue;
        }
       vector<Point> hull;
       convexHull(contours[i],hull,true);
       approxPolyDP(hull,hull,15,true);
        
       RotatedRect bEllipse = fitEllipse(contours.at(i));
       Rect rect = boundingRect(contours[i]);
       int x = (int)bEllipse.center.x;
       int y = (int)bEllipse.center.y;
       int r = (int)rect.width/2;
       //int angle =bEllipse.angle;
       
        
       if (hull.size()<8){
           putText( inPic, "x :"+std::to_string(x), Point(50,180), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       drawContours(inPic,contours,i,Scalar(255,0,0),4);
          putText( inPic, "y :"+std::to_string(y), Point(50,160), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       //drawContours(inPic,contours,i,Scalar(255,0,0),4);
       } 
       bool xOk=false;
       bool yOk=false;
       imshow("inPic",inPic);
   if(r>5&&mode==1){
       if (x>165){
           mur.setPortA(-1);
           mur.setPortB(1);
           xOk=false;
           }
       else if (x<155){
           mur.setPortA(1);
           mur.setPortB(-1);
           xOk=false;
            }
       else {
           mur.setPortA(0);
           mur.setPortB(0);
           xOk=true;           
           }
       if (y>140){//////////
           mur.setPortC(25);
           yOk=false;
           }
       else if (y<130){
           mur.setPortC(-5);
           yOk=false;
            }
       else {
           mur.setPortC(15);
           yOk=true;         
           }   
       }
       if (xOk && yOk){
           toRet=true;
           mur.shoot();
       }
   else if(mode=2){
       if(r>5){
       toRet = true;
       cout<<"true"<<endl;
           }
       else {toRet=false;
       cout<<"false"<<endl;
            }
       }
       return toRet;        
    }
}
bool Centreting(int mode){
   bool toRet=false;
    Mat inPic = mur.getCameraOneFrame();
   if (inPic.empty()){
      cerr<<"Image empty"<<endl;
      toRet=false;
   } 
   Mat green= inPic.clone();
   cvtColor(green, green, CV_BGR2HSV);
   int dopPowerA;
   int dopPowerB;
   Scalar using_upper;
   Scalar using_lower;
   Scalar upper_green(100,255,255);
   Scalar lower_green(42,61,95);
   
   Scalar upper_black(255,255,13);
   Scalar lower_black(0,0,0);
   if (mode == 1){
       using_upper=upper_green;
       using_lower=lower_green;
       }
   else if (mode == 2){
       using_upper=upper_black;
       using_lower=lower_black;
       }
   inRange(green,using_lower,using_upper,green);
   GaussianBlur(green, green, Size(5, 5), 2);
   
   imshow("Centreting",green);
   vector < vector <Point>> contours;
   findContours(green,contours,CV_RETR_TREE,CV_CHAIN_APPROX_NONE);
   
   
   for (size_t i=0;i<contours.size();i++){
       if (contours.at(i).size() < 5) {
            continue;
        }
       vector<Point> hull;
       convexHull(contours[i],hull,true);
       approxPolyDP(hull,hull,15,true);
        
       RotatedRect bEllipse = fitEllipse(contours.at(i));
       //Rect rect = boundingRect(contours[i]);
       int x = (int)bEllipse.center.x;
       int y = (int)bEllipse.center.y;
       //int r = (int)rect.width/2;
       //int angle =bEllipse.angle;
        
        
       if (hull.size()<8){
           putText( inPic, "x :"+std::to_string(x), Point(50,180), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       drawContours(inPic,contours,i,Scalar(255,0,0),4);
          putText( inPic, "y :"+std::to_string(y), Point(50,160), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
       //drawContours(inPic,contours,i,Scalar(255,0,0),4);
       } 
       bool xOk=false;
       bool yOk=false;
       imshow("inPic",inPic);
       if (x<135){
           dopPowerA=15;
           dopPowerB=-15;
           xOk=false;
       }
       else if (x>185){
           dopPowerA=-15;
           dopPowerB=15;
           xOk=false;   
           }
       else {
               dopPowerA=0;
               dopPowerB=0;
               xOk=true;
                          }
           if (y<115){
           mur.setPortA(-5+dopPowerA);
           mur.setPortB(-5+dopPowerB);
           yOk=false;
       }
       else if (y>125){
            mur.setPortA(5+dopPowerA);
           mur.setPortB(5+dopPowerB);
           yOk=false;   
           }
           else {
               
               yOk=true;
                          }
       if (xOk && yOk){
           toRet=true;
       }
       return toRet;
    }       
    
}
    int Gate(){
    Mat image = mur.getCameraTwoFrame();
        
   if (image.empty()){
      cerr<<"Image empty"<<endl;
      return 1000;
   } 
           
        Mat green= image.clone();
        cvtColor(green, green, CV_BGR2HSV);
        Scalar lower_green(53,106,100);
        Scalar upper_green(72,255,255);
          // imshow("hsv",red);
        inRange(green,lower_green,upper_green,green);
        GaussianBlur(green, green, Size(5, 5), 2);
        imshow("green",green);
        //imshow("orig",image);
           waitKey(1);
        vector < vector <Point>> contours;
        findContours(green,contours,CV_RETR_TREE,CV_CHAIN_APPROX_NONE);
           
   
   for (size_t i=0;i<contours.size();i++){
       if (contours.at(i).size() < 5) {
            continue;
        }
       vector<Point> hull;//точки контура
       convexHull(contours[i],hull,true);
       approxPolyDP(hull,hull,15,false);
   
       
       
       RotatedRect bEllipse = fitEllipse(contours.at(i));
       //Rect rect = boundingRect(contours[i]);
       int x = (int)bEllipse.center.x;
       int y = (int)bEllipse.center.y;
       //int r = (int)rect.width/2;
       //int angle =bEllipse.angle;
       //double area = contourArea(contours.at(i));
       
      
       if (hull.size()<8){
       
           putText( image, "x:"+std::to_string(x), Point(50,180), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
           putText( image, "hull size:"+std::to_string(hull.size()), Point(50,220), FONT_HERSHEY_SIMPLEX, 1,Scalar(0, 255, 0), 2, 8 );
           
           circle(image,Point(x,y),2,Scalar(255,0,0),4);    
           drawContours(image,contours,i,Scalar(255,0,0),4);
       }
        
          
        return x;      
       }
       waitKey(1);
   }

