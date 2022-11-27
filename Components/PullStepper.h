#pragma once
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <ArduinoComponents.h>
#include "Util.h"
#include <Stepper.h>

using namespace components;
using namespace std;

class PullStepper:public Component {
public:
	PullStepper(int speed,int step,int pin1,int pin2,int pin3,int pin4):Component(),
		stepper(step,pin1,pin2,pin3,pin4),speed(speed),stepSize(step){
			this->stepper.setSpeed(speed);
			this->running=false;
			this->stepTimer.onInterval([&](){
				if(this->running){
					this->Step();
				}
			},100);
			RegisterChild(stepTimer);
	}
	void Start(){
		this->running=true;
	}

	void Stop(){
		this->running=false;
	}

	bool Running(){
		return this->running;
	}

	void Step(){
		this->stepper.step(this->stepSize/100);
	}

private:
	Stepper stepper;
	int speed;
	int stepSize;
	bool running;
	Timer stepTimer;

	void privateLoop(){

	}
};
