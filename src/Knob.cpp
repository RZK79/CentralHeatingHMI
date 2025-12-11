#include "Knob.h"
#include "Config.h"

Knob* Knob::instance = nullptr;

Knob* Knob::get() {
    if (Knob::instance == nullptr) {
        Knob::instance = new Knob();
    }

    return Knob::instance;
}

Knob::Knob() {
    b = new Button(BUTTON, "knob_button");
    b->addEventListener(this);

    pinMode(ENCODER_A, INPUT_PULLUP);
    pinMode(ENCODER_B, INPUT_PULLUP);

    A_prev_state = digitalRead(ENCODER_A);
    B_prev_state = digitalRead(ENCODER_B);

    position = 0;
    step = 1;
}

void Knob::setListener(KnobListener* newListener) {
    listener = newListener;
}

void Knob::setMinMax(int minPos, int maxPos) {
    minPosition = minPos;
    maxPosition = maxPos;
}

void Knob::update() {
    A_state = digitalRead(ENCODER_A);
    B_state = digitalRead(ENCODER_B);

    if (A_state != A_prev_state && B_state != B_prev_state) {
        if (A_state == HIGH && B_state == LOW) {
            position -= step;
            if (position < minPosition) {
                position = minPosition;
            }
        } else if (A_state == LOW && B_state == LOW) {
            position += step;
            if (position > maxPosition) {
                position = maxPosition;
            }
        }

        if (listener != nullptr) {
            listener->onPositionChange(position);
        }
    }

    A_prev_state = A_state;

    b->update();
}

void Knob::setPosition(int newPosition) {
    position = newPosition;

    if (listener != nullptr) {
        listener->onPositionChange(newPosition);
    }
}

int Knob::getPosition() {
    return position;
}

void Knob::setStep(int newStep){
    step = newStep;
}

void Knob::onButtonPressed(Button* button) {
    if (listener != nullptr) {
        listener->onButtonPressed();
    }
}

void Knob::onButtonReleased(Button* button) {
    if (listener != nullptr) {
        listener->onButtonReleased();
    }
}