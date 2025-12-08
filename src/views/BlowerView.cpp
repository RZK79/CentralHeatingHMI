#include "BlowerView.h"
#include "CurrentState.h"
#include "Controller.h"

void BlowerView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(55, 10);
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->print(message[submenu]);

    Lcd::get()->screen()->setCursor(50, 30);
    Lcd::get()->screen()->setTextSize(2);

    Lcd::get()->screen()->print(BlowerSpeedToValue(static_cast<BlowerSpeed>(selectedPos)));

    Lcd::get()->invalidateView();
}

void BlowerView::reset(int position) {
    message.clear();
    message.push_back("Rozpalanie");
    message.push_back("Stabilizacja");
    message.push_back("Normalne");

    selectedPos = controller->getCurrentState()->blowerSpeedToSetFiringUp;

    Knob::get()->setMinMax(0, 6);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);

    submenu = 0;
}

void BlowerView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void BlowerView::onButtonPressed() {
    if (submenu == 0) {
        controller->getCurrentState()->blowerSpeedToSetFiringUp = static_cast<BlowerSpeed>(selectedPos);
        submenu++;
    } else if (submenu == 1) {
        controller->getCurrentState()->blowerSpeedToSetStabilization = static_cast<BlowerSpeed>(selectedPos);
        submenu++;
    } else if (submenu == 2) {
        controller->getCurrentState()->blowerSpeedToSetNormal = static_cast<BlowerSpeed>(selectedPos);
        controller->getCurrentState()->save();

        controller->getSerialCommunication()->setBlowerSpeedFiringUp(controller->getCurrentState()->blowerSpeedToSetFiringUp);
        controller->getSerialCommunication()->setBlowerSpeedStabilization(controller->getCurrentState()->blowerSpeedToSetStabilization);
        controller->getSerialCommunication()->setBlowerSpeedNormal(controller->getCurrentState()->blowerSpeedToSetNormal);

        controller->changeView("mainMenu", 4);
    }
}