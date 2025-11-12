#ifndef _SERIALCOMMUNICATION_H_
#define _SERIALCOMMUNICATION_H_

#include <Arduino.h>

class SerialCommunication {
    static SerialCommunication *instance;

    char data[32] = { '\0' };
    bool recvInProgress;
    int i;
    const char start = '*';
    const char end = '#';
    SerialCommunication();
public:
    static SerialCommunication* get();


    void serialEvent();
    void reset();

    void turnOn();
    void turnOff();

    void setFeederTime(int time);
    void setFeederPeriod(int time);
    void setBlower(int speed);

    void setCentralHeating(int temperature);
    void getCentralHeating();

    void setHotWater(int temperature);
    void getHotWater();

    void getCentralHeatingPump();
    void getHotWaterPump();

    void getFumes();
    
    void parseData(char* data);
};

#endif