#ifndef _DATASENDER_H_
#define _DATASENDER_H_

#include "Timer.h"

class DataSender : public TimerEventListener {
    Timer* timer;
public:
    DataSender();
    void send();
    void update();

    virtual void onTime(Timer* t) override;
};

#endif