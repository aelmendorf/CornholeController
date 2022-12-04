#include <ArduinoComponents.h>
#include <ArduinoComponents/IO/AnalogInput.h>
#include "CornholeController.h"
#include <Servo.h>
#include <Stepper.h>
#include "./Components/LatchServo.h"
#include "./Components/Util.h"
#include <SR04.h>

/**
 * @author Andrew Elmendorf
 * Class: ELET 3190
 * Team: 2B || !2B
 * Description: Cornhole project controller software
 */

CornholeController controller;

void setup() {
  Serial.begin(38400);
  while(!Serial){
    ;
  }
  Serial.println("Initializing");
  controller.Init();
}

void loop() {
  controller.loop();

}

void serialEvent(){

}
