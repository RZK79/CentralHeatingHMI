#include "Lcd.h"

Lcd* Lcd::instance = nullptr;

Lcd* Lcd::get() {
    if (instance == nullptr) {
        instance = new Lcd();
    }

    return instance;
}

Lcd::Lcd() {
    display = new Adafruit_SSD1306(128, 64, &Wire);
    display->setRotation(0);

    if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        while (true) {

        }
    }

    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->display();
    viewUpdated = true;
}

Adafruit_SSD1306 *Lcd::screen(){
    return display;
}

void Lcd::invalidateView(){
    viewUpdated = false;
}

void Lcd::updateView() {
    if (!viewUpdated) {
        Lcd::get()->screen()->display();
        viewUpdated = true;
    }
}