#ifndef _IOVIEW_H_
#define _IOVIEW_H_

#include "View.h"
#include "Knob.h"

class IOView : public View, public KnobListener {
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif