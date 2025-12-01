#ifndef _SETTINGSVIEW_H_
#define _SETTINGSVIEW_H_

#include "View.h"
#include "Knob.h"

class SettingsView : public View, public KnobListener{
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonPressed() override;
};

#endif