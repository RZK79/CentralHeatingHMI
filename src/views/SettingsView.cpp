#include "SettingsView.h"
#include "Controller.h"

void SettingsView::show() {
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->cp437(true);
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(0, 0);

    Knob::get()->getPosition() == 0 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("NTC");

    Knob::get()->getPosition() == 1 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("Reset");

    Knob::get()->getPosition() == 2 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("Reset Arduino");

    Knob::get()->getPosition() == 3 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("Ust. fabryczne");

    Knob::get()->getPosition() == 4 ? Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE) : Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    Lcd::get()->screen()->println("Powrot");

    Lcd::get()->invalidateView();
}

void SettingsView::reset(int position) {
    Knob::get()->setMinMax(0, 4);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void SettingsView::onPositionChange(int position) {
    show();
}

void SettingsView::onButtonReleased() {
    Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    
    if (Knob::get()->getPosition() == 0) {
        Controller::get()->changeView("NTC");
    } else if (Knob::get()->getPosition() == 1) {
        Controller::get()->reset();
    } else if (Knob::get()->getPosition() == 2) {
        Controller::get()->getSerialCommunication()->resetArduino();
    } else if (Knob::get()->getPosition() == 3) {
        Controller::get()->getCurrentState()->setDefault();
        Controller::get()->getCurrentState()->save();
    } else if (Knob::get()->getPosition() == 4) {
        Controller::get()->changeView("mainMenu", 6);
    }
}