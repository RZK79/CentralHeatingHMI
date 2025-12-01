#include <ESP8266WiFi.h>
#include "IOView.h"
#include "Knob.h"
#include "Controller.h"
#include "CurrentState.h"

void IOView::reset(int position) {
    Knob::get()->setMinMax(0, 0);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void IOView::onPositionChange(int position) {
    show();
}

void IOView::onButtonPressed() {
    controller->changeView("mainMenu", 7);
}

void IOView::show() {
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->cp437(true);
    Lcd::get()->screen()->clearDisplay();

    Lcd::get()->screen()->setCursor(0, 0);

    Lcd::get()->screen()->println("pompa CO: ");
    if (controller->getCurrentState()->isCentralHeatingPumpOn) {
        Lcd::get()->screen()->fillCircle(75, 3, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(75, 3, 3, SSD1306_WHITE);
    }

    Lcd::get()->screen()->println("pompa CWU: ");
    if (controller->getCurrentState()->isHotWaterPumpOn) {
        Lcd::get()->screen()->fillCircle(75, 11, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(75, 11, 3, SSD1306_WHITE);
    }

    Lcd::get()->screen()->println("podajnik: ");
    if(controller->getCurrentState()->isFeederOn){
        Lcd::get()->screen()->fillCircle(75, 19, 3, SSD1306_WHITE);
    }else{
        Lcd::get()->screen()->drawCircle(75, 19, 3, SSD1306_WHITE);
    }
    
    Lcd::get()->screen()->println("grzalka: ");
    if(controller->getCurrentState()->lighter){
        Lcd::get()->screen()->fillCircle(75, 27, 3, SSD1306_WHITE);
    }else{
        Lcd::get()->screen()->drawCircle(75, 27, 3, SSD1306_WHITE);
    }
    
    Lcd::get()->screen()->print("wentylator: ");
    Lcd::get()->screen()->println(controller->getCurrentState()->blowerSpeed);
    
    Lcd::get()->screen()->print("AP: ");
    Lcd::get()->screen()->println(WiFi.SSID());
    Lcd::get()->screen()->print("IP: ");
    Lcd::get()->screen()->println(WiFi.localIP().toString());
    Lcd::get()->invalidateView();
}