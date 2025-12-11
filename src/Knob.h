#ifndef _KNOB_H_
#define _KNOB_H_

#include "Button.h"

class KnobListener {
public:
    virtual void onPositionChange(int position){

    }

    virtual void onButtonReleased(){

    }

    virtual void onButtonPressed(){
        
    }
};

class Knob : public ButtonListener {
    static Knob* instance;
    
    Knob();
    KnobListener* listener;

    Button* b;
    virtual void onButtonPressed(Button* button);
    virtual void onButtonReleased(Button* button);

    int A_state;
    int A_prev_state;
    int B_state;
    int B_prev_state;
    
    int position;
    int minPosition;
    int maxPosition;
    int step;
public:
    static Knob* get();

    void setListener(KnobListener* newListener);

    void update();
    void setPosition(int newPosition);
    void setStep(int newStep);
    int getPosition();
    void setMinMax(int minPos, int maxPos);
};

#endif