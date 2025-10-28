#include "CurrentState.h"

CurrentState* CurrentState::instance = nullptr;

CurrentState* CurrentState::get() {
    if (CurrentState::instance == nullptr) {
        CurrentState::instance = new CurrentState();
    }

    return CurrentState::instance;
}

CurrentState::CurrentState(){
    
}

void CurrentState::setDefault() {
    wifi_connected = false;
    isOn = false;
    isCentralHeatingPumpOn = false;
    isHotWaterPumpOn = false;
    feederTimeToSet = 1000;
    feederPeriodToSet = 1000;
    centralHeatingTemperatureToSet = 55;
    centralHeatingTemperature = 0;
    hotWaterTemperatureToSet = 45;
    hotWaterTemperature = 0;
    blowerSpeedToSet = 750;
    fumesTemperature = 0;
}

void CurrentState::save() {

}

void CurrentState::load() {

}