#ifndef _HOTWATERVIEW_H_
#define _HOTWATERVIEW_H_

#include "View.h"
#include "Knob.h"

class HotWaterView : public View, public KnobListener {
    int selectedPos;
public:
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif