#ifndef _ALERTVIEW_H_
#define _ALERTVIEW_H_

#include "View.h"
#include "Knob.h"

class AlertView : public View, public KnobListener {
    char* message;
public:
    void setMessage(char* msg);

    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif