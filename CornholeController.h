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

class CornholeController:public Component{
public:
    CornholeController():Component(),
        start(STARTB,TriggerOn::Low,InputPull::Up),
        stop(STOPB,TriggerOn::Low,InputPull::Up),
        reset(RESETB,TriggerOn::Low,InputPull::Up),
        latchServo(SERVO,60,90,120),
        pullStepper(12,2048,STEP1,STEP2,STEP3,STEP4),
        rangeFinder(100),indicator(GPIN,BPIN,RPIN){
    }
    void Init(){
        Serial.println("Starting Init, Setup timer");
        this->latchServo.Init();
        this->printTimer.onInterval([&](){
            Serial.print("Distance: ");
            Serial.print(this->rangeFinder.GetDistance());
            Serial.println();
        },500);
         Serial.println("Setup start");
        this->start.onPress([&](){
            this->indicator.TurnOn(Color::BLUE);
            this->latchServo.Open();
            this->pullStepper.Start();
            Serial.println("Start Pressed: Latch Open, Servo Started");
        });
        Serial.println("Setup stop");
        this->stop.onPress([&](){
            this->indicator.TurnOn(Color::GREEN);
            this->latchServo.Close();
            this->pullStepper.Stop();
            Serial.println("Stop Pressed:  Latch Closed, Servo Stopped");
        });
        Serial.println("Setup reset");
        this->reset.onPress([&](){
            this->indicator.TurnOn(Color::RED);
            this->pullStepper.Stop();
            Serial.println("Reset Pressed: System Reset");
        });
        RegisterChild(latchServo);
        RegisterChild(pullStepper);
        RegisterChild(rangeFinder);    
        RegisterChild(printTimer);
        RegisterChild(start);
        RegisterChild(stop);
        RegisterChild(reset);
        this->indicator.TurnOn(Color::GREEN);
        Serial.println("Init Completed");
    }
    // void HandleSerial();
    // void Fire();
    // void Reset();
    // void Start();

private:
    //vector<TactileButton> buttons;
    Timer printTimer,runTimer;
    TactileButton start,stop,reset;
    LatchServo latchServo;
    PullStepper pullStepper;
    RangeFinder rangeFinder;
    RGB indicator;

    void privateLoop(){

    }
};