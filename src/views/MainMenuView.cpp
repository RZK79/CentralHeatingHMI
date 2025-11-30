#include "MainMenuView.h"
#include "Knob.h"
#include "icons.h"
#include "Controller.h"
#include "CurrentState.h"
#include "Debug.h"

MainMenuView::MainMenuView(Controller* parent) : View(parent) {

}

void MainMenuView::reset(int position) {
    Knob::get()->setMinMax(0, 6);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(position);
}

void MainMenuView::pumpStatus() {
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->setCursor(1, 55);
    Lcd::get()->screen()->print("CO");
    if (parentController->getCurrentState()->isCentralHeatingPumpOn) {
        Lcd::get()->screen()->fillCircle(20, 58, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(20, 58, 3, SSD1306_WHITE);
    }
    Lcd::get()->screen()->setCursor(90, 55);
    Lcd::get()->screen()->print("CWU");
    if (parentController->getCurrentState()->isHotWaterPumpOn) {
        Lcd::get()->screen()->fillCircle(115, 58, 3, SSD1306_WHITE);
    } else {
        Lcd::get()->screen()->drawCircle(115, 58, 3, SSD1306_WHITE);
    }

    if (parentController->getCurrentState()->wifiConnected) {
        Lcd::get()->screen()->drawBitmap(120, 0, wifi_bits, wifi_width, wifi_height, SSD1306_WHITE);
    } else {
        if (wifi_blinking) {
            Lcd::get()->screen()->drawBitmap(120, 0, wifi_bits, wifi_width, wifi_height, SSD1306_WHITE);
            wifi_blinking = false;
        } else {
            wifi_blinking = true;
        }
    }

    Lcd::get()->screen()->setTextSize(2);
}

void MainMenuView::onPositionChange(int position) {
    show();
}

void MainMenuView::onButtonPressed() {
    if (Knob::get()->getPosition() == 1) {
        parentController->changeView("firingUp");
    } else if (Knob::get()->getPosition() == 2) {
        parentController->changeView("hotWater");
    } else if (Knob::get()->getPosition() == 3) {
        parentController->changeView("centralHeating");
    } else if (Knob::get()->getPosition() == 4) {
        parentController->changeView("blower");
    } else if (Knob::get()->getPosition() == 5) {
        parentController->changeView("feeder");
    } else if (Knob::get()->getPosition() == 6) {
        parentController->changeView("io");
    }
}

void MainMenuView::showInfo() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->cp437(true);

    Lcd::get()->screen()->setCursor(5, 5);
    String txt = String("temp CO: ");
    txt.concat(parentController->getCurrentState()->centralHeatingTemperature);
    txt.concat((char)0xf8);
    txt.concat('C');
    Lcd::get()->screen()->print(txt);

    Lcd::get()->screen()->setCursor(5, 16);
    txt = String("temp CWU: ");
    txt.concat(parentController->getCurrentState()->hotWaterTemperature);
    txt.concat((char)0xf8);
    txt.concat('C');
    Lcd::get()->screen()->print(txt);

    Lcd::get()->screen()->setCursor(5, 27);
    txt = String("temp spalin: ");
    txt.concat(parentController->getCurrentState()->fumesTemperature);
    txt.concat((char)0xf8);
    txt.concat('C');
    Lcd::get()->screen()->print(txt);

    Lcd::get()->screen()->setTextSize(2);
}

void MainMenuView::showFiringUp() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(5, 7);
    Lcd::get()->screen()->print("Rozpalanie");
    Lcd::get()->screen()->drawXBitmap(48, 27, ogien_bits, ogien_width, ogien_height, SSD1306_WHITE);
}

void MainMenuView::showHotWater() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(1, 7);
    Lcd::get()->screen()->print("Ciepla");
    Lcd::get()->screen()->setCursor(80, 7);
    Lcd::get()->screen()->print("woda");
    Lcd::get()->screen()->drawXBitmap(48, 27, bojler_bits, bojler_width, bojler_height, SSD1306_WHITE);
}

void MainMenuView::showRadiators() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(5, 7);
    Lcd::get()->screen()->print("Kaloryfery");
    Lcd::get()->screen()->drawXBitmap(48, 27, kaloryfer_bits, kaloryfer_width, kaloryfer_height, SSD1306_WHITE);
}

void MainMenuView::showBlower() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(5, 7);
    Lcd::get()->screen()->print("Wentylator");
    Lcd::get()->screen()->drawXBitmap(48, 27, wentylator_bits, wentylator_width, wentylator_height, SSD1306_WHITE);
}

void MainMenuView::showFeeder() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(10, 7);
    Lcd::get()->screen()->print("Podajnik");
    Lcd::get()->screen()->drawXBitmap(48, 27, podajnik_bits, podajnik_width, podajnik_height, SSD1306_WHITE);
}

void MainMenuView::showIO() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(35, 7);
    Lcd::get()->screen()->print("We/Wy");
    Lcd::get()->screen()->drawXBitmap(48, 27, io_bits, io_width, io_height, SSD1306_WHITE);
}


void MainMenuView::show() {
    Lcd::get()->screen()->setTextSize(2);
    if (Knob::get()->getPosition() == 0) {
        showInfo();
    } else if (Knob::get()->getPosition() == 1) {
        showFiringUp();
    } else if (Knob::get()->getPosition() == 2) {
        showHotWater();
    } else if (Knob::get()->getPosition() == 3) {
        showRadiators();
    } else if (Knob::get()->getPosition() == 4) {
        showBlower();
    } else if (Knob::get()->getPosition() == 5) {
        showFeeder();
    } else if (Knob::get()->getPosition() == 6) {
        showIO();
    }

    Debug::State();

    pumpStatus();

    Lcd::get()->invalidateView();
}