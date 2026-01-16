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