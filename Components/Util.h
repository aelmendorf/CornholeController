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

enum SystemState {
    READY, //Latched and ready to fire
    LOADING,  //Motor running, looking for object
    LAUNCHING, // launching then short delay
    INITIALIZING,
};

enum Action{
    Start,
    FIRE,
    RESET,
    LOAD,
    STOP
};

enum Position{
    Load,
    Release,
};

enum Mode{
    Auto,
    Manual  
};

enum Color{
    BLUE,RED,GREEN
};

//Ultrasonic
#define TRIG_PIN    12
#define ECHO_PIN    11 
#define STARTB      0
#define STOPB       13
#define RESETB      2
#define SERVO       10

#define STEP1       6
#define STEP2       7
#define STEP3       8
#define STEP4       9

#define GPIN        4
#define BPIN        5
#define RPIN        3


//Parameters
#define STEPS           200
#define RPM             17
#define DISTANCE        10 //cm
#define RELOAD_DELAY    5000
#define LATCH_ANGLE     120
#define OPEN_ANGLE      90
#define CENTER_ANGLE    60
#define MODE            Mode::Auto
#define MEASURE_N       25.0f
#define FOUND_PERCENT   0.95f
#define INIT_t          5000


