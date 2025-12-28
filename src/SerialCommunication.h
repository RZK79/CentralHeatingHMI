#ifndef _SERIALCOMMUNICATION_H_
#define _SERIALCOMMUNICATION_H_

#include <Arduino.h>

class SerialCommunication {
    char data[32] = { '\0' };
    bool recvInProgress;
    int i;
    const char start = '*';
    const char end = '#';
    void init();
public:
    SerialCommunication();
    void serialEvent();
    void parseData(char* data);

    void turnOn();
    void turnOff();

    void setFeederTime(int time);
    void setFeederPeriod(int time);
    void setBlowerSpeedFiringUp(int speed);
    void setBlowerSpeedStabilization(int speed);
    void setBlowerSpeedNormal(int speed);
    void setCentralHeatingTemperature(int temperature);
    void getCentralHeatingTemperature();

    void setHotWaterTemperature(int temperature);
    void getHotWaterTemperature();
    void getHotWaterPump();

    void getCentralHeatingPump();
    void getLighter();
    void getBlowerSpeed();
    void getFeeder();

    void getFumesTemperature();

    void getError();
    void resetError();

    void resetArduino();

    void setNTCCHType(int ntcType);
    void setNTCHWType(int ntcType);

    void turnCentralHeatingPumpOn();
    void turnCentralHeatingPumpOff();
    void turnHotWaterPumpOn();
    void turnHotWaterPumpOff();

    void setFiringUpTime(int time);
    void setStabilizationTime(int time);

};

#endif