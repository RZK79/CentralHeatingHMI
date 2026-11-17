#include "AlertView.h"
#include "Controller.h"
#include "Errors.h"
#include "alert.h"

void AlertView::setMessage(char* msg)
{
    message = msg;
}

void AlertView::show()
{
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->setCursor(0, 0);
    Lcd::get()->screen()->print(message);
    Lcd::get()->screen()->drawXBitmap(48, 27, alert_bits, alert_width, alert_height, SSD1306_WHITE);
}

void AlertView::reset(int position)
{
    show();
}

void AlertView::onPositionChange(int position)
{
}

void AlertView::onButtonReleased()
{
    message = (char*)"\0";
    Controller::get()->getSerialCommunication()->resetError();
    Controller::get()->getCurrentState()->error = CentralHeating::Errors::OK;
    Controller::get()->changeView("mainMenu", 1);
}
