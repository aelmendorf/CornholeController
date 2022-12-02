#pragma once
#include <ArduinoComponents.h>
#include <SR04.h>
#include "Util.h"

using namespace components;
using namespace std;

#define filter   .1
#define mTime    100

class RangeFinder:public Component{
public:
    RangeFinder(long present):Component(),
    sr04(ECHO_PIN,TRIG_PIN),objectPresent(present){  
        this->distance=0;
        RegisterChild(this->timer);
    // this->timer.onInterval([&](){
    //     this->Measure();
    // },mTime);
    }

    bool ObjectPresent(){
        this->Measure();
        return this->distance<=this->objectPresent;
    }

    void Measure(){
        this->distance=this->sr04.Distance();
    }

    double GetDistance(){
        return this->distance;
    }
    
private:
    Timer timer;
    SR04 sr04;
    long objectPresent;
    double distance;

    void privateLoop(){ }
};

