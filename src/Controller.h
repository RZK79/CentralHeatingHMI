#ifndef _CONTROLLERSTATE_H_
#define _CONTROLLERSTATE_H_

#include <Arduino.h>
#include <map>
#include "Timer.h"
#include "View.h"

class Controller : public TimerEventListener{
    static Controller* instance;
    Controller();

    Timer *updateDataTimer;

    std::map<String, View*> views;
    String currentView;
public:
    static Controller* get();

    void setup();
    void loop();

    void changeView(String viewName, int position = 0);

    virtual void onTime(Timer* timer);
};

#endif