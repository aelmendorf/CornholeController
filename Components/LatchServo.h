#pragma once
#include <Arduino.h>
#include <ArduinoComponents.h>
#include <Servo.h>
#include "Util.h"

using namespace components;
using namespace std;

enum LatchState{
	OPEN,
	CLOSE
};

class LatchServo:public Component {
public:
	LatchServo(int pin,int open,int mid,int close):Component(),
	openAngle(open),closeAngle(close),centerAngle(mid){	
	}

	void Init(){
		this->servo.attach(SERVO);
		this->servo.write(90);
	}

	void Open(){
		this->servo.write(this->openAngle);
		this->state=LatchState::OPEN;
	}

	void Close(){
		this->servo.write(this->closeAngle);
		this->state=LatchState::CLOSE;
	}

	LatchState Toggle(){
		if(this->state==LatchState::OPEN){
			this->Close();
			return this->state;
		}else{
			this->Open();
			return this->state;
		}
	}

private:
	Servo servo;
	LatchState state;
	int openAngle;
	int closeAngle;
	int centerAngle;

	void privateLoop(){}
};
