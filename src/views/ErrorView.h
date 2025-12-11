#ifndef _ERRORVIEW_H_
#define _ERRORVIEW_H_

#include "View.h"
#include "Knob.h"

class ErrorView : public View, public KnobListener {
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif