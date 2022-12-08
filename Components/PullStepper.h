#pragma once
#include <Arduino.h>
#include <ArduinoComponents.h>
#include "Util.h"
#include <bi_polar_Stepper.h>
/**
 * @author Andrew Elmendorf
 * Class: ELET 3190
 * Team: 2B || !2B
 * Description: Cornhole project controller software
 */

using namespace components;

class PullStepper:public Component {
public:
	PullStepper(int speed,int step,int pin1,int pin2,int pin3,int pin4):Component(),
		stepper(pin4,pin3,pin2,pin1),speed(speed),stepSize(step){
			 this->stepper.set_step_per_rev(this->stepSize);
			 this->stepper.set_RPM(this->speed);
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
		this->stepper.rotate_CCW();
	}

private:
	bi_polar_Stepper stepper;
	int speed;
	int stepSize;
	bool running;
	Timer stepTimer;

	void privateLoop(){

	}
};