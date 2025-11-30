#include "AlertView.h"
#include "Controller.h"
#include "alert.h"

AlertView::AlertView(Controller* parent) : View(parent){

}

void AlertView::setMessage(char* msg) {
    message = msg;
}

void AlertView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->setCursor(0, 0);
    Lcd::get()->screen()->print(message);
    Lcd::get()->screen()->drawXBitmap(48, 27, alert_bits, alert_width, alert_height, SSD1306_WHITE);
}

void AlertView::reset(int position) {
    show();
}

void AlertView::onPositionChange(int position) {

}

void AlertView::onButtonPressed() {
    message = (char*)"\0";
    parentController->changeView("mainMenu", 1);
}
