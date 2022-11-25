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
        this->timer.onInterval([&](){
            this->Measure();
        },mTime);
    }

    bool ObjectPresent(){
        return this->distance<=this->objectPresent;
    }

    void Measure(){
        this->sr04.Ping();
        long dist=this->sr04.getDistance();
        this->distance+=(dist-this->distance)*filter;
    }
    
private:
    Timer timer;
    SR04 sr04;
    long objectPresent;
    double distance;

    void privateLoop(){ }
};

