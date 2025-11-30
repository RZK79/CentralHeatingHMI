#include "BlowerView.h"
#include "CurrentState.h"
#include "Controller.h"

BlowerView::BlowerView(Controller* parent) : View(parent) {

}

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
    selectedPos = parentController->getCurrentState()->blowerSpeedToSet;
    Knob::get()->setMinMax(700, 1000);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
    Knob::get()->setStep(10);
}

void BlowerView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void BlowerView::onButtonPressed() {
    parentController->getCurrentState()->blowerSpeedToSet = selectedPos;
    parentController->getCurrentState()->save();
    parentController->getSerialCommunication()->setBlower(selectedPos);
    Knob::get()->setStep(1);
    controller->changeView("mainMenu", 4);
}