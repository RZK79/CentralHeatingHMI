#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <Arduino.h>
#include <map>

using namespace std;

class Button;

class ButtonListener{
public:
    virtual void onButtonPressed(Button *button) = 0;
    virtual void onButtonReleased(Button *button) = 0;
};

enum ButtonState{
    IDLE,
    RELEASED,
    PRESSED
};

class Button{
    ButtonState state;
    std::map<u32, ButtonListener*> listeners;
    uint8_t readPin;
    String name;    
public:
    Button(uint8_t pin, String buttonName);
    void addEventListener(ButtonListener *listener);
    void update();
    String getName();
};

#endif