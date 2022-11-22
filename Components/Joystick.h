#pragma once
#include <ArduinoComponents.h>

using namespace components;
using namespace std;

class Joystick: public Component{
public:
    Joystick(PinNumber yPin,PinNumber xPin):Component(),yInput(yPin),xInput(xPin){

    }

private:
    AnalogInput yInput;
    AnalogInput xInput;
};

