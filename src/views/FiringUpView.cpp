#include "FiringUpView.h"
#include "Lcd.h"
#include "Controller.h"
#include "CurrentState.h"

FiringUpView::FiringUpView(Controller* parent) : View(parent) {

}

void FiringUpView::reset(int position) {
    selectedPos = position;
    Knob::get()->setMinMax(0, 1);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void FiringUpView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void FiringUpView::onButtonPressed() {
    if (selectedPos == 0) {
        parentController->getSerialCommunication()->turnOn();
        parentController->getCurrentState()->isOn = true;
    } else {
        parentController->getSerialCommunication()->turnOff();
        parentController->getCurrentState()->isOn = false;
    }

    Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    parentController->changeView("mainMenu", 1);
}

void FiringUpView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->setCursor(0, 0);
    Knob::get()->getPosition() == 0 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("Wlacz");
    Knob::get()->getPosition() == 1 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("Wylacz");
    Lcd::get()->invalidateView();
}