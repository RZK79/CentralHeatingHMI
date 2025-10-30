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
    selectedPos = CurrentState::get()->feederTimeToSet;
    currentParam = 0;
    Knob::get()->setMinMax(800, 2000);
    Knob::get()->setListener(this);
    Knob::get()->setPosition(selectedPos);
    Knob::get()->setStep(10);
}

void FeederView::onPositionChange(int position) {
    selectedPos = position;
    show();
}

void FeederView::onButtonPressed() {
    if(currentParam == 0){
        CurrentState::get()->feederTimeToSet = selectedPos;
        currentParam = 1;
        selectedPos = CurrentState::get()->feederPeriodToSet;
        Knob::get()->setPosition(selectedPos);
    }else{
        CurrentState::get()->feederPeriodToSet = selectedPos;
        CurrentState::get()->save();
        SerialCommunication::get()->setFeederTime(CurrentState::get()->feederTimeToSet);
        SerialCommunication::get()->setFeederPeriod(CurrentState::get()->feederPeriodToSet);
        Knob::get()->setStep(1);
        Controller::get()->changeView("mainMenu", 5);
    }
}