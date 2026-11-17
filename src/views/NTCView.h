#ifndef _NTCVIEW_H_
#define _NTCVIEW_H_

#include "View.h"
#include "Knob.h"

class NTCView : public View, public KnobListener {
    uint8_t currentNTC;
    int ntcType;
    void printCurrentNTC();
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif