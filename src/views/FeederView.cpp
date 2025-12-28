#include "FeederView.h"
#include "CurrentState.h"
#include "Controller.h"

void FeederView::show() {
    Lcd::get()->screen()->clearDisplay();
    Lcd::get()->screen()->setCursor(35, 5);
    Lcd::get()->screen()->setTextSize(1);
    if(currentParam == 0){
        Lcd::get()->screen()->print("podawanie");
    }else {
        Lcd::get()->screen()->print("interwal");
    }
    Lcd::get()->screen()->setCursor(50, 20);
    Lcd::get()->screen()->setTextSize(2);
    Lcd::get()->screen()->print(selectedPos);   

    Lcd::get()->invalidateView();
}

void FeederView::reset(int position) {
    selectedPos = Controller::get()->getCurrentState()->feederTimeToSet;
    currentParam = 0;
    Knob::get()->setMinMax(0, 10000);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
    Knob::get()->setStep(100);
}

void FeederView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void FeederView::onButtonReleased() {
    if(currentParam == 0){
        Controller::get()->getCurrentState()->feederTimeToSet = selectedPos;
        currentParam = 1;
        selectedPos = Controller::get()->getCurrentState()->feederPeriodToSet;
        Knob::get()->setPosition(selectedPos);
    }else{
        Controller::get()->getCurrentState()->feederPeriodToSet = selectedPos;
        Controller::get()->getCurrentState()->save();
        Controller::get()->getSerialCommunication()->setFeederTime(Controller::get()->getCurrentState()->feederTimeToSet);
        Controller::get()->getSerialCommunication()->setFeederPeriod(Controller::get()->getCurrentState()->feederPeriodToSet);
        Knob::get()->setStep(1);
        Controller::get()->changeView("mainMenu", 5);
    }
}