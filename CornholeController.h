#pragma once
#include <ArduinoComponents.h>
#include <avr/wdt.h>
#include "./Components/Util.h"
#include "./Components/LatchServo.h"
#include "./Components/PullStepper.h"
#include "./Components/RangeFinder.h"
#include "./Components/RGB.h"

using namespace components;
using namespace std;

class CornholeController:public Component{
public:
    CornholeController():Component(),
        start(STARTB,TriggerOn::Low,InputPull::Up),
        stop(STOPB,TriggerOn::Low,InputPull::Up),
        reset(RESETB,TriggerOn::Low,InputPull::Up),
        latchServo(SERVO,OPEN_ANGLE,LATCH_ANGLE,CENTER_ANGLE),
        pullStepper(RPM,STEPS,STEP1,STEP2,STEP3,STEP4),
        rangeFinder(DISTANCE),indicator(GPIN,BPIN,RPIN){
    }
    void Init();
    void Fire();
    void Load();
    void Stop();
    void Reset();
    void Start();
    void FindStartState();
    void ProcessButton(Action action);

private:
    //vector<TactileButton> buttons;
    Timer printTimer,launchTimer;
    TactileButton start,stop,reset;
    LatchServo latchServo;
    PullStepper pullStepper;
    RangeFinder rangeFinder;
    RGB indicator;
    SystemState state;
    long tlaunch=0;
    long tinit=0;
    bool systemStarted=false;
    float foundCount=0;
    float lookCount=0;

    void InitAuto();
    void InitManual();
    bool ObjectFound();
    void privateLoop();
};