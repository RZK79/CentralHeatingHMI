#ifndef _FEEDERVIEW_H_
#define _FEEDERVIEW_H_

#include "View.h"
#include "Knob.h"

class FeederView : public View, public KnobListener {
    int selectedPos;
    int currentParam;
public:
    FeederView(Controller* parent);
    
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif