#include "ErrorView.h"
#include "Controller.h"
#include "alert.h"
#include "CurrentState.h"
#include "Errors.h"

void ErrorView::show() {

}

void ErrorView::reset(int position) {
    Knob::get()->setMinMax(0, 0);
    Knob::get()->setListener(this);
}

void ErrorView::onPositionChange(int position) {
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->cp437(true);
    Lcd::get()->screen()->clearDisplay();

    Lcd::get()->screen()->drawXBitmap(48, 2, alert_bits, alert_width, alert_height, SSD1306_WHITE);

    Lcd::get()->screen()->setCursor(0, 37);
    const char* msg = "";
    switch (controller->getCurrentState()->error) {
        case CentralHeating::Errors::FIRING_UP_TIMEOUT:
            msg = "Zbyt dlugi czas rozpalania!";
            break;

        case CentralHeating::Errors::STABILIZATION_TIMEOUT:
            msg = "Zbyt dlugi czas stabilizacji!";
            break;

        case CentralHeating::Errors::FUMES_TEMPERATURE_TOO_HIGH:
            msg = "Zbyt wysoka temperatura spalin!";
            break;

    }

    Lcd::get()->screen()->print(msg);
    Lcd::get()->invalidateView();
}

void ErrorView::onButtonPressed() {
    controller->changeView("mainMenu", 0);
}
