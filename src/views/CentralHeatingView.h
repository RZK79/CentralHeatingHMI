#ifndef _CENTRALHEATINGVIEW_H_
#define _CENTRALHEATINGVIEW_H_

#include "View.h"
#include "Knob.h"

class CentralHeatingView : public View, public KnobListener {
    int selectedPos;
public:
    CentralHeatingView(Controller* parent);
    
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif