#ifndef _ALERTVIEW_H_
#define _ALERTVIEW_H_

#include "View.h"
#include "Knob.h"

class AlertView : public View, public KnobListener {
    char* message;
public:
    AlertView(Controller* parent);
    
    void setMessage(char* msg);

    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif