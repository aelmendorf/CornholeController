#pragma once
#include <Arduino.h>
#include <ArduinoComponents.h>
#include "Util.h"
/**
 * @author Andrew Elmendorf
 * Class: ELET 3190
 * Team: 2B || !2B
 * Description: Cornhole project controller software
 */

using namespace components;
using namespace std;

class RGB:public Component{
public:
    RGB(int gPin,int bPin, int rPin):Component(),
        green(gPin),red(rPin),blue(bPin){
    }

    void TurnOn(Color color){
        switch(color){
            case Color::BLUE:{
                this->blue.high();
                this->green.low();
                this->red.low();
                break;
            }
            case Color::GREEN:{
                this->blue.low();
                this->green.high();
                this->red.low();
                break;
            }
            case Color::RED:{
                this->blue.low();
                this->green.low();
                this->red.high();
                break;
            }

        }
    }

private:
    DigitalOutput green;
    DigitalOutput red;
    DigitalOutput blue;

    void privateLoop(){ }

};
