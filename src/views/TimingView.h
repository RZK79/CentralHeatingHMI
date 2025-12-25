#ifndef _TIMINGVIEW_H_
#define _TIMINGVIEW_H_

#include "View.h"
#include "Knob.h"

class TimingView : public View, public KnobListener {
    int currentParam;
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif