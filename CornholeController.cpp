#include "CornholeController.h"
/**
 * @author Andrew Elmendorf
 * Class: ELET 3190
 * Team: 2B || !2B
 * Description: Cornhole project controller software
 */

void CornholeController::Init(){
    this->systemStarted=false;
    if(MODE==Mode::Auto){
        this->InitAuto();
    }else{
        this->InitManual();
    }
}

void CornholeController::InitAuto(){
    RegisterChild(this->latchServo);
    RegisterChild(this->pullStepper);
    RegisterChild(this->rangeFinder); 
    RegisterChild(this->start);
    RegisterChild(this->stop);
    RegisterChild(this->reset);
    RegisterChild(this->printTimer);
    RegisterChild(this->buzzer);
    this->latchServo.Init();

//May remove
    if(this->latchServo.GetState()==LatchState::UNKNOWN){
        this->latchServo.Close();   
    }   

    this->printTimer.onInterval([&](){
        Serial.print("Distance: ");
        this->rangeFinder.Measure();
        Serial.print(this->rangeFinder.GetDistance());
        Serial.println();
    },1000);

    this->start.onPress([&](){
        if(!this->systemStarted){
            this->systemStarted=true;
            this->ProcessButton(Action::Start);
        }else{
            this->ProcessButton(Action::FIRE);
        }
    });

    this->stop.onPress([&](){
        this->ProcessButton(Action::STOP);
    });

    this->reset.onPress([&](){
        this->ProcessButton(Action::RESET);
    });
}

void CornholeController::InitManual(){

    Serial.println("Starting Init, Setup timer");
    this->latchServo.Init();
    this->printTimer.onInterval([&](){
        Serial.print("Distance: ");
        this->rangeFinder.Measure();
        Serial.print(this->rangeFinder.GetDistance());
        Serial.println();
    },1000);
    Serial.println("Setup start");
    this->start.onPress([&](){
        this->indicator.TurnOn(Color::BLUE);
        this->buzzer.StartSong();
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


void CornholeController::ProcessButton(Action action){
    switch(action){
        case Action::Start:{
            this->Start();
            break;
        }
        case Action::FIRE:{
            if(this->state==SystemState::READY){
                this->Fire();
            }
            break;
        }
        case Action::LOAD:{
            if(this->state!=SystemState::READY 
            && this->state!=SystemState::LOADING){
                this->Load();
            }
        }
        case Action::RESET:{
            this->Reset();
            break;
        }
        case Action::STOP:{
            this->Stop();
        }
    }
}

void CornholeController::Reset(){
    Serial.println("Resetting Device");
    this->pullStepper.Stop();
    wdt_disable();
    wdt_enable(WDTO_15MS);
    while(1){;}
}

void CornholeController::Load(){
    Serial.println("Loading,Looking for object..");
    this->state=SystemState::LOADING;
    this->latchServo.Open();
    this->pullStepper.Start();
    this->indicator.TurnOn(Color::BLUE);
}

void CornholeController::Fire(){
    Serial.println("Launching..");
    this->state=SystemState::LAUNCHING;
    this->indicator.TurnOn(Color::RED);
    delay(500);
    this->latchServo.Open();
    this->tlaunch=millis();
}

void CornholeController::Stop(){
    Serial.println("Stopping System..");
    this->systemStarted=false;
    this->pullStepper.Stop();
    this->indicator.TurnOn(Color::RED);
}

void CornholeController::FindStartState(){
    if(this->ObjectFound()){
        this->state=SystemState::READY;
    }else{
        this->Load();
    }
}

void CornholeController::Start(){
    this->state=SystemState::INITIALIZING;
    this->buzzer.StartSong();
    this->indicator.TurnOn(Color::BLUE);
    this->tinit=millis();
}

bool CornholeController::ObjectFound(){
    if(this->rangeFinder.ObjectPresent()){
        this->foundCount++;
    }
    lookCount++;
    if(this->lookCount>=MEASURE_N){
        auto ret=(foundCount/MEASURE_N)>FOUND_PERCENT; 
        this->lookCount=0;
        this->foundCount=0;
        return ret;
    }else{
        return false;
    }
}

void CornholeController::privateLoop(){
    if(this->state==SystemState::LOADING){
        if(this->ObjectFound()){
            Serial.println("Object Found,Loading Complete..");
            Serial.println("System Ready, press start to fire...");
            this->pullStepper.Stop();
            this->latchServo.Close();
            this->indicator.TurnOn(Color::GREEN);
            this->state=SystemState::READY;
        }
    }else if(this->state==SystemState::LAUNCHING){
        if((millis()-this->tlaunch)>=RELOAD_DELAY){
            Serial.println("Launching Complete, Starting Reload..");
            this->Load();
            this->tlaunch=0;
        }
    }else if(this->state==SystemState::INITIALIZING){
        if((millis()-this->tinit)>=INIT_t){
            this->Load();
        }else{
            if(this->ObjectFound()){
                Serial.println("Object Found,Loading Complete..");
                Serial.println("System Ready, press start to fire...");
                this->indicator.TurnOn(Color::GREEN);
                this->state=SystemState::READY;
            }
        }
    }
}