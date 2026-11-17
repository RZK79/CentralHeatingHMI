#ifndef _CONTROLLERSTATE_H_
#define _CONTROLLERSTATE_H_

#include <Arduino.h>
#include <map>
#include "Timer.h"
#include "View.h"
#include "CurrentState.h"
#include "SerialCommunication.h"
#include "DataSender.h"

class Controller : public TimerEventListener {
public:
    enum State {
        OFF,
        FIRING_UP_PREBLOW,
        FIRING_UP_PREBLOW_DONE,
        PREFEED,
        PREFEED_DONE,
        FIRING_UP,
        STABILIZATION,
        NORMAL,
        CLEANING,
        EXTINCTION
    };
private:
    static Controller* instance;

    Timer* updateDataTimer;
    Timer* updateTempTimer;

    std::map<String, View*> views;
    String currentView;
    CurrentState* state;
    SerialCommunication* se;
    DataSender* ds;
    Controller();
public:
    static Controller* get();

    void setup();
    void loop();

    void changeView(String viewName, int position = 0);
    CurrentState* getCurrentState();
    SerialCommunication* getSerialCommunication();
    void updateParameters();
    void reset();

    virtual void onTime(Timer* timer);
};
#endif