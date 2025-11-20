#include "Debug.h"
#include "Lcd.h"

ControllerState Debug::state = ControllerState::OFF;

void Debug::Log(const char* str) {
    if (DEBUG) {
        Lcd::get()->screen()->setCursor(0, 0);
        Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        Lcd::get()->screen()->print(str);
        Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    }
}

void Debug::State() {
    if (DEBUG) {
        Lcd::get()->screen()->setCursor(0, 0);
        Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE);

        switch (state) {
            case OFF:
                Lcd::get()->screen()->print("OFF");
                break;
            case FIRING_UP_PREBLOW:
                Lcd::get()->screen()->print("PREBLOW");
                break;
            case PREFEED:
                Lcd::get()->screen()->print("PREFEED");
                break;
            case FIRING_UP:
                Lcd::get()->screen()->print("FIRIN UP");
                break;
            case STABILIZATION:
                Lcd::get()->screen()->print("STABILIZATION");
                break;
            case NORMAL:
                Lcd::get()->screen()->print("NORMAL");
                break;
            case CLEANING:
                Lcd::get()->screen()->print("CLEANING");
                break;
            case EXTINCTION:
                Lcd::get()->screen()->print("EXTINCTION");
                break;
        }

        Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    }
}