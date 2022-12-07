#pragma once

#include <Arduino.h>
#include <ArduinoComponents.h>
#include <Servo.h>
#include "Util.h"

using namespace components;


class Buzzer:public Component{

public:
    Buzzer():Component(){

    }

    void StartSong(){
        this->songStarted=true;
        this->thisNote=0;
    }

    void StopSong(){
        this->songStarted=false;
    }

private:
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;
    int divider = 0;
    int noteDuration = 0;
    int tempo = 108;
    int buzzer = 1;
    bool songStarted=false;
    int thisNote=0;


    void privateLoop(){
        if(songStarted){
            if(this->thisNote<notes * 2){
                // calculates the duration of each note
                divider = melody[thisNote + 1];
                if (divider > 0) {
                    // regular note, just proceed
                    noteDuration = (wholenote) / divider;
                } else if (divider < 0) {
                    // dotted notes are represented with negative durations!!
                    noteDuration = (wholenote) / abs(divider);
                    noteDuration *= 1.5; // increases the duration in half for dotted notes
                }
                // we only play the note for 90% of the duration, leaving 10% as a pause
                tone(buzzer, melody[thisNote], noteDuration*0.9);
                // Wait for the specief duration before playing the next note.
                delay(noteDuration);
                
                // stop the waveform generation before the next note.
                noTone(buzzer);
                this->thisNote=this->thisNote+2;
            }else{
                this->songStarted=false;
                this->thisNote=0;
            }
        }
    }
};


