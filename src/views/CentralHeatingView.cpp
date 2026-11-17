#include "CentralHeatingView.h"
#include "Controller.h"
#include "CurrentState.h"

void CentralHeatingView::show()
{
    Lcd::get()->screen()->clearDisplay();
    
    if (submenu == 0) {
        Lcd::get()->screen()->setCursor(35, 10);
        Lcd::get()->screen()->setTextSize(1);
        Lcd::get()->screen()->print("temperatura");

        Lcd::get()->screen()->setCursor(55, 30);
        Lcd::get()->screen()->setTextSize(2);
        Lcd::get()->screen()->print(selectedPos);
    } else {
        Lcd::get()->screen()->setCursor(0, 0);
        Lcd::get()->screen()->setTextSize(2);

        if (selectedPos == 0) {
            Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        } else {
            Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        }
        Lcd::get()->screen()->println("wlacz");
        if (selectedPos == 1) {
            Lcd::get()->screen()->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        } else {
            Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        }
        Lcd::get()->screen()->print("wylacz");
    }

    Lcd::get()->invalidateView();
}

void CentralHeatingView::reset(int position)
{
    selectedPos = Controller::get()->getCurrentState()->centralHeatingTemperatureToSet;
    submenu = 0;
    Knob::get()->setMinMax(50, 80);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void CentralHeatingView::onPositionChange(int position)
{
    selectedPos = position;
    show();
}

void CentralHeatingView::onButtonReleased()
{
    if (submenu == 0) {
        submenu++;
        Controller::get()->getCurrentState()->centralHeatingTemperatureToSet = selectedPos;
        Controller::get()->getCurrentState()->save();
        Controller::get()->getSerialCommunication()->setCentralHeatingTemperature(selectedPos);

        Knob::get()->setMinMax(0, 1);
        selectedPos = Controller::get()->getCurrentState()->isCentralHeatingPumpOn ? 0 : 1;
        Knob::get()->setPosition(selectedPos);
    } else {
        Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        if (selectedPos == 0) {
            Controller::get()->getCurrentState()->isCentralHeatingPumpOn = true;
            Controller::get()->getSerialCommunication()->turnCentralHeatingPumpOn();
        } else {
            Controller::get()->getCurrentState()->isCentralHeatingPumpOn = false;
            Controller::get()->getSerialCommunication()->turnCentralHeatingPumpOff();
        }
        Lcd::get()->screen()->setTextSize(1);
        Controller::get()->changeView("mainMenu", 3);
    }
}