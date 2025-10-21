#ifndef _CURRENTSTATE_H_
#define _CURRENTSTATE_H_

class CurrentState {
public:
    static bool isOn;
    static bool isCentralHeatingPumpOn;
    static bool isHotWaterPumpOn;
    static int feederTimeToSet;
    static int feederPeriodToSet;
    static int centralHeatingTemperatureToSet;
    static int centralHeatingTemperature;
    static int hotWaterTemperatureToSet;
    static int hotWaterTemperature;
    static int blowerSpeedToSet;
    static int fumesTemperature;

    static void setDefault(){
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

    static void save(){

    }

    static void load(){

    }
};

#endif