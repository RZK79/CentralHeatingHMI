#ifndef _SERIALCOMMUNICATION_H_
#define _SERIALCOMMUNICATION_H_

#include <Arduino.h>

class SerialCommunication {
    char data[32] = { '\0' };
    bool recvInProgress;
    int i;
    const char start = '*';
    const char end = '#';
public:
    SerialCommunication();
    
    void serialEvent();
    void reset();

    void turnOn();
    void turnOff();

    void setFeederTime(int time);
    void setFeederPeriod(int time);
    void setBlowerSpeed(int speed);
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

    void resetArduino();

    void parseData(char* data);
};

#endif