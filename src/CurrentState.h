#ifndef _CURRENTSTATE_H_
#define _CURRENTSTATE_H_
#include "BlowerSpeed.h"

#define SAVE_VERSION    0x0003

class CurrentState {
public:
    CurrentState();

    bool wifiConnected;
    bool isOn;
    bool isCentralHeatingPumpOn;
    bool isHotWaterPumpOn;
    bool lighter;
    bool isFeederOn;
    int feederTimeToSet;
    int feederPeriodToSet;
    int centralHeatingTemperatureToSet;
    int hotWaterTemperatureToSet;
    int blowerSpeedToSetFiringUp;
    int blowerSpeedToSetStabilization;
    int blowerSpeedToSetNormal;
    int blowerSpeed;
    int centralHeatingTemperature;
    int hotWaterTemperature;
    int fumesTemperature;
    int error;
    int NTCch;
    int NTChw;
    int firingUpTimeToSet;
    int stabilizationTimeToSet;
    
    void setDefault();

    void save();
    void load();
};

#endif