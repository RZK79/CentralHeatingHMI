#include "BlowerView.h"
#include "CurrentState.h"
#include "Controller.h"

void BlowerView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(30, 10);
    Lcd::get()->screen()->setTextSize(1);
    Lcd::get()->screen()->print(message[submenu]);

    Lcd::get()->screen()->setCursor(35, 30);
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->print(selectedPos);
    Lcd::get()->screen()->print("%");

    Lcd::get()->invalidateView();
}

void BlowerView::reset(int position) {
    message.clear();
    message.push_back("Rozpalanie");
    message.push_back("Stabilizacja");
    message.push_back("Normalne");

    selectedPos = Controller::get()->getCurrentState()->blowerSpeedToSetFiringUp;
    submenu = 0;
    
    Knob::get()->setMinMax(0, 100);
    Knob::get()->setStep(5);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);

}

void BlowerView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void BlowerView::onButtonReleased() {
    if (submenu == 0) {
        Controller::get()->getCurrentState()->blowerSpeedToSetFiringUp = selectedPos;
        selectedPos = Controller::get()->getCurrentState()->blowerSpeedToSetStabilization;
        Knob::get()->setPosition(selectedPos);
        submenu++;
        show();
    } else if (submenu == 1) {
        Controller::get()->getCurrentState()->blowerSpeedToSetStabilization = selectedPos;
        selectedPos = Controller::get()->getCurrentState()->blowerSpeedToSetNormal;
        Knob::get()->setPosition(selectedPos);
        submenu++;
        show();
    } else if (submenu == 2) {
        Controller::get()->getCurrentState()->blowerSpeedToSetNormal = selectedPos;
        Controller::get()->getCurrentState()->save();

        Controller::get()->getSerialCommunication()->setBlowerSpeedFiringUp(Controller::get()->getCurrentState()->blowerSpeedToSetFiringUp);
        Controller::get()->getSerialCommunication()->setBlowerSpeedStabilization(Controller::get()->getCurrentState()->blowerSpeedToSetStabilization);
        Controller::get()->getSerialCommunication()->setBlowerSpeedNormal(Controller::get()->getCurrentState()->blowerSpeedToSetNormal);

        Controller::get()->changeView("mainMenu", 4);
    }
}