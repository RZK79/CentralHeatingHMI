#ifndef _MAINMENUVIEW_H_
#define _MAINMENUVIEW_H_

#include "View.h"
#include "Knob.h"

class MainMenuView : public View, public KnobListener {
    void pumpStatus();
    bool wifi_blinking;
public:
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif