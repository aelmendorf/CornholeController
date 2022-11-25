#pragma once
#include <ArduinoComponents.h>
#include "./Components/Util.h"
#include "./Components/LatchServo.h"
#include "./Components/PullStepper.h"
#include "./Components/RangeFinder.h"
#include "./Components/RGB.h"

using namespace components;
using namespace std;

class ControllerState{
public:
    Mode mode;
    SystemState state;
    SystemSettings settings;
private:
    
};

class CornholeController{
public:
    CornholeController();
    void Init();
    void HandleSerial();
    void Fire();
    void Reset();
    void Start();

private:
    vector<TactileButton> buttons;
    LatchServo latchServo;
    PullStepper pullStepper;
    RangeFinder rangeFinder;
    RGB indicator;
};