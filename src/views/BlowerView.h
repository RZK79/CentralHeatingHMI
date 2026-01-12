#ifndef _BLOWERVIEW_H_
#define _BLOWERVIEW_H_

#include <vector>
#include "View.h"
#include "Knob.h"

using namespace std;

class BlowerView : public View, public KnobListener {
    int selectedPos;
    uint8_t submenu;
    vector<const char*> message;
public:
    void show() override;
    void reset(int position = 0) override;

    void onPositionChange(int position) override;
    void onButtonReleased() override;
};

#endif