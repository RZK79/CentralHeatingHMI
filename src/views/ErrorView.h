#ifndef _ERRORVIEW_H_
#define _ERRORVIEW_H_

#include "View.h"
#include "Knob.h"

class ErrorView : public View, public KnobListener {
public:
    virtual void show();
    virtual void reset(int position = 0);

    virtual void onPositionChange(int position);
    virtual void onButtonPressed();
};

#endif