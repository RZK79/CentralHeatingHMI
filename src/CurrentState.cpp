#include "CurrentState.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "Errors.h"
#include "BlowerSpeed.h"
#include "NTCType.h"

CurrentState::CurrentState() {
    EEPROM.begin(512);
    setDefault();
    load();
}

void CurrentState::setDefault() {
    wifiConnected = false;
    isOn = false;;
    isCentralHeatingPumpOn = false;
    isHotWaterPumpOn = false;
    lighter = false;
    isFeederOn = false;
    feederTimeToSet = 2000;
    feederPeriodToSet = 3000;
    centralHeatingTemperatureToSet = 55;
    hotWaterTemperatureToSet = 45;
    blowerSpeedToSetFiringUp = BlowerSpeed::RPM_2500;
    blowerSpeedToSetStabilization = BlowerSpeed::RPM_3000;
    blowerSpeedToSetNormal = BlowerSpeed::RPM_2000;
    blowerSpeed = BlowerSpeed::RPM_0;
    centralHeatingTemperature = 0;
    hotWaterTemperature = 0;
    fumesTemperature = 0;
    error = CentralHeating::Errors::OK;
    NTCch = NTC_10k;
    NTChw = NTC_5k;
}

void CurrentState::save() {
    uint16_t save_marker = SAVE_VERSION;
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
    EEPROM.put(offset, blowerSpeedToSetFiringUp);
    offset += sizeof(int);
    EEPROM.put(offset, blowerSpeedToSetStabilization);
    offset += sizeof(int);
    EEPROM.put(offset, blowerSpeedToSetNormal);
    offset += sizeof(int);
    EEPROM.put(offset, NTCch);
    offset += sizeof(int);
    EEPROM.put(offset, NTChw);
    EEPROM.commit();
}

void CurrentState::load() {
    uint16_t save_marker = 0;
    EEPROM.get(0, save_marker);

    if (save_marker != SAVE_VERSION) {
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
    EEPROM.get(offset, blowerSpeedToSetFiringUp);
    offset += sizeof(int);
    EEPROM.get(offset, blowerSpeedToSetStabilization);
    offset += sizeof(int);
    EEPROM.get(offset, blowerSpeedToSetNormal);
    offset += sizeof(int);
    EEPROM.get(offset, NTCch);
    offset += sizeof(int);
    EEPROM.get(offset, NTChw);
}
