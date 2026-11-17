#ifndef _FEEDERVIEW_H_
#define _FEEDERVIEW_H_

#include "View.h"
#include "Knob.h"

class FeederView : public View, public KnobListener {
    int selectedPos;
    int currentParam;
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif