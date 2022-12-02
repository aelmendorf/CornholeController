#pragma once
#include <Arduino.h>
#include <ArduinoComponents.h>
#include <Servo.h>
#include "Util.h"

using namespace components;
using namespace std;

enum LatchState{
	OPEN,
	CLOSE,
	UNKNOWN
};

class LatchServo:public Component {
public:
	LatchServo(int pin,int open,int mid,int close):Component(),
	openAngle(open),closeAngle(close),centerAngle(mid){	
	}

	void Init(){
		this->servo.attach(SERVO);
	}

	void Open(){
		this->servo.write(this->openAngle);
		this->state=LatchState::OPEN;
	}

	void Close(){
		this->servo.write(this->closeAngle);
		this->state=LatchState::CLOSE;
	}

	LatchState GetState(){
		int angle=this->servo.read();
		switch (angle){
			case LATCH_ANGLE:{
				this->state=LatchState::CLOSE;
				break;
			}
			case OPEN_ANGLE:{
				this->state=LatchState::OPEN;
				break;
			}
			default:{
				this->state=LatchState::UNKNOWN;
				break;
			} 
		}
		return this->state;
	}

	LatchState Toggle(){
		switch(this->state){
			case LatchState::OPEN:{
				this->state=LatchState::CLOSE;
				this->Close();
				break;
			}
			case LatchState::CLOSE:{
				this->state=LatchState::OPEN;
				this->Open();
				break;
			}
			case LatchState::UNKNOWN:{
				Serial.println("Unknown state,manually open or close");
				break;
			}
		}
		return this->state;
	}

private:
	Servo servo;
	LatchState state;
	int openAngle;
	int closeAngle;
	int centerAngle;

	void privateLoop(){}
};
