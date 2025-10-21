#ifndef _IOVIEW_H_
#define _IOVIEW_H_

#include "View.h"
#include "Knob.h"

class IOView : public View, public KnobListener{
public:
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif