#ifndef _FIRINGUP_H_
#define _FIRINGUP_H_

#include "View.h"
#include "Knob.h"

class FiringUpView : public View, public KnobListener {
    int selectedPos;
public:
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif