#include "BlowerView.h"
#include "CurrentState.h"
#include "Controller.h"

void BlowerView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(55, 10);
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->print("RPM");
    
    Lcd::get()->screen()->setCursor(50, 30);
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->print(selectedPos);

    Lcd::get()->invalidateView();
}

void BlowerView::reset(int position) {
    selectedPos = CurrentState::get()->blowerSpeedToSet;
    Knob::get()->setMinMax(700, 1000);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void BlowerView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void BlowerView::onButtonPressed() {
    CurrentState::get()->blowerSpeedToSet = selectedPos;
    Controller::get()->changeView("mainMenu", 4);
}