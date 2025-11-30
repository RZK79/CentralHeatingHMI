#include "FeederView.h"
#include "CurrentState.h"
#include "Controller.h"

FeederView::FeederView(Controller* parent) : View(parent){
    
}

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
    selectedPos = parentController->getCurrentState()->feederTimeToSet;
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
        parentController->getCurrentState()->feederTimeToSet = selectedPos;
        currentParam = 1;
        selectedPos = parentController->getCurrentState()->feederPeriodToSet;
        Knob::get()->setPosition(selectedPos);
    }else{
        parentController->getCurrentState()->feederPeriodToSet = selectedPos;
        parentController->getCurrentState()->save();
        parentController->getSerialCommunication()->setFeederTime(parentController->getCurrentState()->feederTimeToSet);
        parentController->getSerialCommunication()->setFeederPeriod(parentController->getCurrentState()->feederPeriodToSet);
        Knob::get()->setStep(1);
        parentController->changeView("mainMenu", 5);
    }
}