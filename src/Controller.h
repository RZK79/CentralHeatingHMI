#ifndef _CONTROLLERSTATE_H_
#define _CONTROLLERSTATE_H_

#include <Arduino.h>
#include <map>
#include "Timer.h"
#include "View.h"
#include "CurrentState.h"
#include "SerialCommunication.h"

class Controller : public TimerEventListener {
    Timer* updateDataTimer;

    std::map<String, View*> views;
    String currentView;
    CurrentState* state;
    SerialCommunication* se;
public:
    Controller();

    void setup();
    void loop();

    void changeView(String viewName, int position = 0);
    CurrentState* getCurrentState();
    SerialCommunication* getSerialCommunication();

    virtual void onTime(Timer* timer);
};

extern Controller* controller;
#endif