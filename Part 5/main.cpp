//PID

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <math.h>
using namespace std;
int initialpitch, initialroll, initialheight, a;
long long int timeofflight;


struct Quadrocopter{                                           //contains all values of the quadrocopter
public:
    int hoverheight;
    float PIDheight;                                       //these are the calculated PID values for pitch and roll
    float height, last_height[2];
    int engines[4];                                        //contains the strength of the engines
    float inteheight;                 //contains a sum for the integrals of pitch and roll
    float last_errors[2][2];                               //first index: pitch/roll second index: current or last value
    float heightvelocity;     //individual velocities for both pitch and roll
    void setFR(int d){                                     //the next four functions set the engine strength
        engines[0] = d;
    }
    void setFL(int d){
        engines[1] = d;
    }
    void setBR(int d){
        engines[2] = d;
    }
    void setBL(int d){
        engines[3] = d;
    }
    int getHeight(){
        return height;
    }
    void lastvaluesupdate(int currentheight){
        last_height[1] = last_height[0];
        last_height[0] = hoverheight-currentheight;
    }
} Q;

float abs(float a){          //a simple, but useful function for the absolute value of an integer
    if(a<0){
        return -a;
    }
    return a;
}

void changePIDHeight(int a, int b, int c){
    Q.PIDheight = a*Q.last_height[0]+b*Q.inteheight+c*(Q.last_height[0]-Q.last_height[1]);
}

void calculate(){
    changePIDHeight(40, 3, 13);                      //this can be tuned for more optimal results
    Q.setFL(0);
    Q.setFR(0);
    Q.setBL(0);
    Q.setBR(0);
    for(int x = 0; x<4; x++){
        Q.engines[x] = Q.PIDheight/4;
    }
    /*for(int x = 0; x<4; x++){                      //the engines can't have a thrust greater than the max or min
        if(Q.engines[x]>255){
            Q.engines[x] = 255;
        }
        if(Q.engines[x]<-255){
            Q.engines[x] = -255;
        }
    }*/
}


void update(){
    Q.heightvelocity += (float)(Q.engines[1]+Q.engines[3]+Q.engines[0]+Q.engines[2])/50-10; //-10 accounts for gravity
    Q.height+=Q.heightvelocity;
    Q.inteheight+=Q.hoverheight-Q.getHeight();
    Q.lastvaluesupdate(Q.getHeight());
}

void delay(){
    for(int x = 0; x<(1<<25); x++){
    }
    timeofflight++;
}

void space(int x){                        //encorporates logarithms to create a stable chart
    int a = 0;
    if(x<0){                              //if x<0, the negative sign takes up one extra space
        a = (int)log10(-x);               //the logarithm returns the number of digits for the positive value of x
        for(int x = 0; x<10-(a+1); x++){
            cout<<" ";
        }
    }
    else if (x>0){                        //if x>0, there is no negative sign, so we need to add an extra space
        a = (int)log10(x);                //the logarithm returns the number of digits
        for(int x = 0; x<10-(a); x++){
            cout<<" ";
        }
    }
    else{                                 //if x = 0, the logarithm is undefined. This conditional accounts for the case
        for(int x = 0; x<10; x++){
            cout<<" ";
        }
    }
}

void display(){
    cout<<Q.getHeight(); space(Q.getHeight());
    cout<<Q.engines[0]; space(Q.engines[0]);    //the rest of the lines display the engine strength
    cout<<Q.engines[1]; space(Q.engines[1]);
    cout<<Q.engines[2]; space(Q.engines[2]);
    cout<<Q.engines[3];  space(Q.engines[3]);
    cout<<Q.last_height[0];  space(Q.last_height[0]);
    cout<<Q.inteheight; space(Q.inteheight);
    cout<<Q.PIDheight<<endl;
}


void test(){
    while(1){
        delay();                                                            //delays the appearance of the information
        calculate();                                                        //calculates the new engine values
        update();                                                           //updates the values and velocities of pitch and roll
        if(Q.getHeight() == Q.hoverheight){              //tracks the time until the copter is stabilized
            a++;
        }
        else{
            a = 0;                                                          //this resets a if unstable
        }
        if(a == 5 && Q.getHeight() == Q.hoverheight){
            display();
            cout<<"Yay, your Quadrocopter is stabilized!"<<endl;   //one possible ending: the copter is stabilized
            cout<<"Time: "<<timeofflight<<endl;                    //displays the time
            return;
        }
        display();                                                 //displays the values
    }
}

int main() {
    cout<<"Initial height: "<<endl;
    cin>>initialheight;
    cout<<"Desired height: "<<endl;
    cin>>Q.hoverheight;
    Q.height = initialheight;
    Q.last_height[0] = Q.hoverheight-initialheight;
    Q.last_height[1] = Q.hoverheight-initialheight;
    cout<<"Height     Engine 1:  Engine 2:  Engine 3: Engine 4:   Prop:      Integral:  Deriv:"<<endl;   //starts the chart
    display();                                                                 //displays the inital values in the chart
    test();                                                                    //begins the PID controller test
}
