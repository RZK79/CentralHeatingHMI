#ifndef _MAINMENUVIEW_H_
#define _MAINMENUVIEW_H_

#include "View.h"
#include "Knob.h"

class MainMenuView : public View, public KnobListener {
    void pumpStatus();
    bool wifi_blinking;
    
    void showInfo();
    void showFiringUp();
    void showHotWater();
    void showRadiators();
    void showBlower();
    void showFeeder();
    void showSettings();
    void showIO();
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonPressed() override;
};

#endif