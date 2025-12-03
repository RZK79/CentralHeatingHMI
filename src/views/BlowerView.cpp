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

    Lcd::get()->screen()->print(BlowerSpeedToValue(static_cast<BlowerSpeed>(selectedPos)));

    Lcd::get()->invalidateView();
}

void BlowerView::reset(int position) {
    selectedPos = controller->getCurrentState()->blowerSpeedToSet;
    Knob::get()->setMinMax(0, 6);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void BlowerView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void BlowerView::onButtonPressed() {
    controller->getCurrentState()->blowerSpeedToSet = static_cast<BlowerSpeed>(selectedPos);
    controller->getCurrentState()->save();
    controller->getSerialCommunication()->setBlowerSpeed(selectedPos);
    controller->changeView("mainMenu", 4);
}