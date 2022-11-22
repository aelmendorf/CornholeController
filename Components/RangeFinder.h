#pragma once
#include <ArduinoComponents.h>
#include <SR04.h>
#include "Util.h"

using namespace components;
using namespace std;

class RangeFinder:public Component{
public:
    RangeFinder():Component(),sr04(ECHO_PIN,TRIG_PIN){  }

    long GetDistance(){
        return this->sr04.getDistance();
    }
    
private:
    SR04 sr04;
    long distance;
};

