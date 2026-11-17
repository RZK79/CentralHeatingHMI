#include "Button.h"

Button::Button(uint8_t pin, String buttonName) {
    name = buttonName;
    readPin = pin;
    state = RELEASED;
    pinMode(readPin, INPUT_PULLUP);
}

void Button::addEventListener(ButtonListener* listener) {
    listeners[readPin] = listener;
}

void Button::update() {
    int currentState = digitalRead(readPin);

    if (state == RELEASED && currentState == LOW) {
        state = PRESSED;
        listeners[readPin]->onButtonPressed(this);
    } else if (state == PRESSED && currentState == HIGH) {
        state = RELEASED;
        listeners[readPin]->onButtonReleased(this);
    }
}

String Button::getName() {
    return name;
}