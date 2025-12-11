#ifndef _CENTRALHEATINGVIEW_H_
#define _CENTRALHEATINGVIEW_H_

#include "View.h"
#include "Knob.h"

class CentralHeatingView : public View, public KnobListener {
    int selectedPos;
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif