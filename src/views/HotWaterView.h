#ifndef _HOTWATERVIEW_H_
#define _HOTWATERVIEW_H_

#include "View.h"
#include "Knob.h"

class HotWaterView : public View, public KnobListener {
    int selectedPos;
    int submenu;
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif