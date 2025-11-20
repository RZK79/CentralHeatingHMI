#ifndef _CURRENTSTATE_H_
#define _CURRENTSTATE_H_

class CurrentState {
    static CurrentState* instance;
    CurrentState();
public:
    static CurrentState* get();

    bool wifiConnected;
    
    bool isOn;
    bool isCentralHeatingPumpOn;
    bool isHotWaterPumpOn;
    bool isBlowerOn;

    bool isLighterOn;

    int feederTimeToSet;
    int feederPeriodToSet;

    int centralHeatingTemperatureToSet;
    int hotWaterTemperatureToSet;
    
    int blowerSpeedToSet;

    int centralHeatingTemperature;
    int hotWaterTemperature;
    int fumesTemperature;

    int error;

    void setDefault();
    void save();
    void load();
};

#endif