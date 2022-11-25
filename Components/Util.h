#pragma once
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

template <class T> int EEPROM_write(int addr, const T& value) {
    const byte* p = (const byte*)(const void*)&value;
    int newAddr;
    for (newAddr = 0; newAddr < sizeof(value); newAddr++) {
        EEPROM.write(addr++, *p++);
    }
    return newAddr;
}//End write any value/type

template <class T> int EEPROM_read(int addr, T& value) {
    byte* p = (byte*)(void*)&value;
    int newAddr;
    for (newAddr = 0; newAddr < sizeof(value); newAddr++)
        *p++ = EEPROM.read(addr++);
    return newAddr;
}//End read any value/type


struct SystemSettings{
    long BeanBagPresent;
    int ReloadDelay;
    int StepperSpeed;
    int OpenAngle;
    int CloseAngle;
    int MidAngle;
    int StepSize;
};

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

enum Color{
    BLUE,RED,GREEN
};

//Ultrasonic
#define TRIG_PIN 12
#define ECHO_PIN 11 

//