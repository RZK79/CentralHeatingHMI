#include "HotWaterView.h"
#include "Controller.h"
#include "CurrentState.h"

void HotWaterView::show()
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

void HotWaterView::reset(int position)
{
    selectedPos = Controller::get()->getCurrentState()->hotWaterTemperatureToSet;
    submenu = 0;
    Knob::get()->setMinMax(40, 70);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
}

void HotWaterView::onPositionChange(int position)
{
    selectedPos = position;
    show();
}

void HotWaterView::onButtonReleased()
{
    if (submenu == 0) {
        submenu++;
        Controller::get()->getCurrentState()->hotWaterTemperatureToSet = selectedPos;
        Controller::get()->getCurrentState()->save();
        Controller::get()->getSerialCommunication()->setHotWaterTemperature(selectedPos);

        Knob::get()->setMinMax(0, 1);
        selectedPos = Controller::get()->getCurrentState()->isHotWaterPumpOn ? 0 : 1;
        Knob::get()->setPosition(selectedPos);
    } else {
        Lcd::get()->screen()->setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        if (selectedPos == 0) {
            Controller::get()->getCurrentState()->isHotWaterPumpOn = true;
            Controller::get()->getSerialCommunication()->turnHotWaterPumpOn();
        } else {
            Controller::get()->getCurrentState()->isHotWaterPumpOn = false;
            Controller::get()->getSerialCommunication()->turnHotWaterPumpOff();
        }
        Lcd::get()->screen()->setTextSize(1);
        Controller::get()->changeView("mainMenu", 2);
    }
}