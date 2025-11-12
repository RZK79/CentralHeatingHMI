#include "FiringUpView.h"
#include "Lcd.h"
#include "Controller.h"
#include "CurrentState.h"

void FiringUpView::reset(int position) {
    selectedPos = 0;
    Knob::get()->setMinMax(0, 1);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void FiringUpView::onPositionChange(int position) {
    show();
}

void FiringUpView::onButtonPressed() {
    if(selectedPos == 0){
        SerialCommunication::get()->turnOn();
        CurrentState::get()->isOn = true;
    }else{
        SerialCommunication::get()->turnOff();
        CurrentState::get()->isOn = false;
    }
    
    Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Controller::get()->changeView("mainMenu", 1);
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