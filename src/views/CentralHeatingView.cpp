#include "CentralHeatingView.h"
#include "CurrentState.h"
#include "Controller.h"

void CentralHeatingView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(35, 10);
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->print("temperatura");

    Lcd::get()->screen()->setCursor(55, 30);
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->print(selectedPos);

    Lcd::get()->invalidateView();
}

void CentralHeatingView::reset(int position) {
    selectedPos = controller->getCurrentState()->centralHeatingTemperatureToSet;
    Knob::get()->setMinMax(50, 80);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void CentralHeatingView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void CentralHeatingView::onButtonReleased() {
    controller->getCurrentState()->centralHeatingTemperatureToSet = selectedPos;
    controller->getCurrentState()->save();
    controller->getSerialCommunication()->setCentralHeatingTemperature(selectedPos);
    controller->changeView("mainMenu", 3);
}