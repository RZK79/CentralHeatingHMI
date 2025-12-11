#include "HotWaterView.h"
#include "CurrentState.h"
#include "Controller.h"

void HotWaterView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(35, 10);
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->print("temperatura");

    Lcd::get()->screen()->setCursor(55, 30);
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->print(selectedPos);

    Lcd::get()->invalidateView();
}

void HotWaterView::reset(int position) {
    selectedPos = controller->getCurrentState()->hotWaterTemperatureToSet;
    Knob::get()->setMinMax(40, 70);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void HotWaterView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void HotWaterView::onButtonReleased() {
    controller->getCurrentState()->hotWaterTemperatureToSet = selectedPos;
    controller->getCurrentState()->save();
    controller->getSerialCommunication()->setHotWaterTemperature(selectedPos);
    controller->changeView("mainMenu", 2);
}