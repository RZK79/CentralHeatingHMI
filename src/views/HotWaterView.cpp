#include "HotWaterView.h"
#include "CurrentState.h"
#include "Controller.h"

HotWaterView::HotWaterView(Controller* parent) : View(parent) {

}

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
    selectedPos = parentController->getCurrentState()->hotWaterTemperatureToSet;
    Knob::get()->setMinMax(40, 70);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void HotWaterView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void HotWaterView::onButtonPressed() {
    parentController->getCurrentState()->hotWaterTemperatureToSet = selectedPos;
    parentController->getCurrentState()->save();
    parentController->getSerialCommunication()->setHotWater(selectedPos);
    parentController->changeView("mainMenu", 2);
}