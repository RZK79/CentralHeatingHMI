#include "NTCView.h"
#include "Controller.h"
#include "NTCType.h"

void NTCView::printCurrentNTC() {
    switch (ntcType) {
        case NTC_5k:
            Lcd::get()->screen()->println("5k");
            break;

        case NTC_10k:
            Lcd::get()->screen()->println("10k");
            break;

        case NTC_15k:
            Lcd::get()->screen()->println("15k");
            break;

        case NTC_20k:
            Lcd::get()->screen()->println("20k");
            break;
    }
}

void NTCView::show() {
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->cp437(true);
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(0, 0);

    if (currentNTC == 0) {
        Lcd::get()->screen()->println("NTC CO");
        printCurrentNTC();
    } else if (currentNTC == 1) {
        Lcd::get()->screen()->println("NTC CWU");
        printCurrentNTC();
    }

    Lcd::get()->invalidateView();
}

void NTCView::reset(int position) {
    currentNTC = 0;
    ntcType = Controller::get()->getCurrentState()->NTCch;
    Knob::get()->setMinMax(0, NTCTypeSize - 1);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(ntcType);
}

void NTCView::onPositionChange(int position) {
    ntcType = position;
    show();
}

void NTCView::onButtonReleased() {
    if (currentNTC == 0) {
        Controller::get()->getCurrentState()->NTCch = ntcType;
        ntcType = Controller::get()->getCurrentState()->NTChw;
        currentNTC++;
        show();
    } else if (currentNTC == 1) {
        Controller::get()->getCurrentState()->NTChw = ntcType;
        Controller::get()->getCurrentState()->save();

        Controller::get()->getSerialCommunication()->setNTCCHType(Controller::get()->getCurrentState()->NTCch);
        Controller::get()->getSerialCommunication()->setNTCHWType(Controller::get()->getCurrentState()->NTChw);

        Lcd::get()->screen()->setTextSize(1);
        Controller::get()->changeView("settings");
    }
}