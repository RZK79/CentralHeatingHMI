#ifndef _BLOWERVIEW_H_
#define _BLOWERVIEW_H_

#include "View.h"
#include "Knob.h"

class BlowerView : public View, public KnobListener {
    int selectedPos;
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonPressed() override;
};

#endif