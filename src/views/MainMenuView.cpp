#include "MainMenuView.h"
#include "Knob.h"
#include "icons.h"
#include "Controller.h"
#include "CurrentState.h"

void MainMenuView::reset(int position) {
    Knob::get()->setMinMax(0, 6);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void MainMenuView::pumpStatus() {
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->setCursor(1, 55);
    Lcd::get()->screen()->print("CO");
    if (CurrentState::get()->isCentralHeatingPumpOn) {
        Lcd::get()->screen()->fillCircle(20, 58, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(20, 58, 3, SSD1306_WHITE);
    }
    Lcd::get()->screen()->setCursor(90, 55);
    Lcd::get()->screen()->print("CWU");
    if (CurrentState::get()->isHotWaterPumpOn) {
        Lcd::get()->screen()->fillCircle(115, 58, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(115, 58, 3, SSD1306_WHITE);

    }

    if (CurrentState::get()->wifi_connected) {
        Lcd::get()->screen()->drawBitmap(120, 0, wifi_bits, wifi_width, wifi_height, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawBitmap(120, 0, no_wifi_bits, no_wifi_width, no_wifi_height, SSD1306_WHITE);
    }

    Lcd::get()->screen()->setTextSize(2);
}

void MainMenuView::onPositionChange(int position) {
    show();
}

void MainMenuView::onButtonPressed() {
    if (Knob::get()->getPosition() == 1) {
        Controller::get()->changeView("firingUp");
    } else if (Knob::get()->getPosition() == 2) {
        Controller::get()->changeView("hotWater");
    } else if (Knob::get()->getPosition() == 3) {
        Controller::get()->changeView("centralHeating");
    } else if (Knob::get()->getPosition() == 4) {
        Controller::get()->changeView("blower");
    } else if (Knob::get()->getPosition() == 5) {
        Controller::get()->changeView("feeder");
    } else if (Knob::get()->getPosition() == 6) {
        Controller::get()->changeView("io");
    }
}

void MainMenuView::show() {
    Lcd::get()->screen()->setTextSize(2);
    if (Knob::get()->getPosition() == 0) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setTextSize(1);
        Lcd::get()->screen()->cp437(true);

        Lcd::get()->screen()->setCursor(5, 5);
        String txt = String("temp CO: ");
        txt.concat(55);
        txt.concat((char)0xf8);
        txt.concat('C');
        Lcd::get()->screen()->print(txt);

        Lcd::get()->screen()->setCursor(5, 16);
        txt = String("temp CWU: ");
        txt.concat(45);
        txt.concat((char)0xf8);
        txt.concat('C');
        Lcd::get()->screen()->print(txt);

        Lcd::get()->screen()->setCursor(5, 27);
        txt = String("temp spalin: ");
        txt.concat(CurrentState::get()->fumesTemperature);
        txt.concat((char)0xf8);
        txt.concat('C');
        Lcd::get()->screen()->print(txt);

        Lcd::get()->screen()->setTextSize(2);
    } else if (Knob::get()->getPosition() == 1) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setCursor(5, 7);
        Lcd::get()->screen()->print("Rozpalanie");
        Lcd::get()->screen()->drawXBitmap(48, 27, ogien_bits, ogien_width, ogien_height, SSD1306_WHITE);
    } else if (Knob::get()->getPosition() == 2) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setCursor(1, 7);
        Lcd::get()->screen()->print("Ciepla");
        Lcd::get()->screen()->setCursor(80, 7);
        Lcd::get()->screen()->print("woda");
        Lcd::get()->screen()->drawXBitmap(48, 27, bojler_bits, bojler_width, bojler_height, SSD1306_WHITE);
    } else if (Knob::get()->getPosition() == 3) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setCursor(5, 7);
        Lcd::get()->screen()->print("Kaloryfery");
        Lcd::get()->screen()->drawXBitmap(48, 27, kaloryfer_bits, kaloryfer_width, kaloryfer_height, SSD1306_WHITE);
    } else if (Knob::get()->getPosition() == 4) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setCursor(5, 7);
        Lcd::get()->screen()->print("Wentylator");
        Lcd::get()->screen()->drawXBitmap(48, 27, wentylator_bits, wentylator_width, wentylator_height, SSD1306_WHITE);
    } else if (Knob::get()->getPosition() == 5) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setCursor(10, 7);
        Lcd::get()->screen()->print("Podajnik");
        Lcd::get()->screen()->drawXBitmap(48, 27, podajnik_bits, podajnik_width, podajnik_height, SSD1306_WHITE);
    } else if (Knob::get()->getPosition() == 6) {
        Lcd::get()->screen()->clearDisplay();
        Lcd::get()->screen()->setCursor(35, 7);
        Lcd::get()->screen()->print("We/Wy");
        Lcd::get()->screen()->drawXBitmap(48, 27, io_bits, io_width, io_height, SSD1306_WHITE);
    }

    pumpStatus();

    Lcd::get()->invalidateView();
}