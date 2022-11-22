#pragma once
#include <ArduinoComponents.h>

using namespace components;
using namespace std;

enum SystemState {
	Running,
	Idle,
	Paused,
	Warmup,
};

enum Position{
    Load,
    Release,
};

enum Mode{
    Auto,
    Manual,
    Debug  
};

class ControllerState{
public:
    Mode mode;
    SystemState state;
private:
    
};

class CornholeController{
public:
    void Init();
    void HandleSerial();
private:


};