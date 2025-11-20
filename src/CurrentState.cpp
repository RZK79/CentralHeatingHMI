#include "CurrentState.h"
#include <EEPROM.h>
#include <Arduino.h>

CurrentState* CurrentState::instance = nullptr;

CurrentState* CurrentState::get() {
    if (CurrentState::instance == nullptr) {
        CurrentState::instance = new CurrentState();
    }

    return CurrentState::instance;
}

CurrentState::CurrentState(){
    EEPROM.begin(512);
    load();
}

void CurrentState::setDefault() {
    wifiConnected = false;
    isOn = false;
    isCentralHeatingPumpOn = false;
    isHotWaterPumpOn = false;
    isLighterOn = false;
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
    uint16_t save_marker = 0xcafe;
    int offset = 0;
    EEPROM.put(offset, save_marker);
    offset += sizeof(uint16_t);
    EEPROM.put(offset, feederTimeToSet);
    offset += sizeof(int);
    EEPROM.put(offset, feederPeriodToSet);
    offset += sizeof(int);
    EEPROM.put(offset, centralHeatingTemperatureToSet);
    offset += sizeof(int);
    EEPROM.put(offset, hotWaterTemperatureToSet);
    offset += sizeof(int);
    EEPROM.put(offset, blowerSpeedToSet);
    EEPROM.commit();
}

void CurrentState::load() {
    uint16_t save_marker = 0;
    EEPROM.get(0, save_marker);
    
    if (save_marker != 0xcafe) {
        setDefault();
        save();
    }
    
    int offset = 0;
    offset += sizeof(uint16_t);
    EEPROM.get(offset, feederTimeToSet);
    offset += sizeof(int);
    EEPROM.get(offset, feederPeriodToSet);
    offset += sizeof(int);
    EEPROM.get(offset, centralHeatingTemperatureToSet);
    offset += sizeof(int);
    EEPROM.get(offset, hotWaterTemperatureToSet);
    offset += sizeof(int);
    EEPROM.get(offset, blowerSpeedToSet);
}