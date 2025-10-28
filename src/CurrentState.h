#ifndef _CURRENTSTATE_H_
#define _CURRENTSTATE_H_

class CurrentState {
    static CurrentState* instance;
    CurrentState();
public:
    static CurrentState* get();

    bool wifi_connected;
    bool isOn;
    bool isCentralHeatingPumpOn;
    bool isHotWaterPumpOn;

    int feederTimeToSet;
    int feederPeriodToSet;
    int centralHeatingTemperatureToSet;
    int hotWaterTemperatureToSet;
    int blowerSpeedToSet;

    int centralHeatingTemperature;
    int hotWaterTemperature;
    int fumesTemperature;

    void setDefault();
    void save();
    void load();
};

#endif