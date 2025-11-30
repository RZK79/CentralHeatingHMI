#include <ESP8266WiFi.h>
#include "IOView.h"
#include "Knob.h"
#include "Controller.h"
#include "CurrentState.h"

IOView::IOView(Controller* parent) : View(parent) {

}

void IOView::reset(int position) {
    Knob::get()->setMinMax(0, 0);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void IOView::onPositionChange(int position) {
    show();
}

void IOView::onButtonPressed() {
    parentController->changeView("mainMenu", 6);
}

void IOView::show() {
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->cp437(true);
    Lcd::get()->screen()->clearDisplay();

    Lcd::get()->screen()->setCursor(0, 0);

    Lcd::get()->screen()->println("pompa CO: ");
    if (parentController->getCurrentState()->isCentralHeatingPumpOn) {
        Lcd::get()->screen()->fillCircle(75, 3, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(75, 3, 3, SSD1306_WHITE);
    }

    Lcd::get()->screen()->println("pompa CWU: ");
    if (parentController->getCurrentState()->isHotWaterPumpOn) {
        Lcd::get()->screen()->fillCircle(75, 11, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(75, 11, 3, SSD1306_WHITE);
    }

    Lcd::get()->screen()->println("podajnik: ");
    Lcd::get()->screen()->drawCircle(75, 27, 3, SSD1306_WHITE);
    
    Lcd::get()->screen()->println("grzalka: ");
    Lcd::get()->screen()->drawCircle(75, 36, 3, SSD1306_WHITE);
    
    Lcd::get()->screen()->println("wentylator: ");
    Lcd::get()->screen()->println(parentController->getCurrentState()->blowerSpeed);
    
    Lcd::get()->screen()->print("AP: ");
    Lcd::get()->screen()->println(WiFi.SSID());
    Lcd::get()->screen()->print("IP: ");
    Lcd::get()->screen()->println(WiFi.localIP().toString());
    Lcd::get()->invalidateView();
}