#pragma once
#include <ArduinoComponents.h>

using namespace components;
using namespace std;

class Joystick: public Component{
public:
    Joystick(PinNumber ypin,PinNumber xPin):Component()

private:
    AnalogInput YInput;
    AnalogInput XInput;
};

