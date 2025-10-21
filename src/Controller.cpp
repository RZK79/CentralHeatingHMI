#include "Config.h"
#include "Controller.h"
#include "CurrentState.h"
#include "SerialCommunication.h"
#include "Knob.h"
#include "views/Views.h"

Controller* Controller::instance = nullptr;

Controller::Controller() {
}

Controller* Controller::get() {
    if (Controller::instance == nullptr) {
        Controller::instance = new Controller();
    }

    return Controller::instance;
}

void Controller::setup() {
    updateDataTimer = new Timer();
    updateDataTimer->addEventListener(this);
    updateDataTimer->start(UPDATE_DATA_TIME);

    views["mainMenu"] = new MainMenuView();
    views["firingUp"] = new FiringUpView();
    views["hotWater"] = new HotWaterView();
    views["centralHeating"] = new CentralHeatingView();
    views["blower"] = new BlowerView();
    views["feeder"] = new FeederView();
    views["io"] = new IOView();

    changeView("mainMenu");
}

void Controller::changeView(String viewName, int position) {
    currentView = viewName;
    views[currentView]->reset(position);
}

void Controller::loop() {
    Knob::get()->update();
    Lcd::get()->updateView();
}

void Controller::onTime(Timer* timer) {
    if (timer == updateDataTimer) {
        SerialCommunication::get()->getHotWater();
        SerialCommunication::get()->getCentralHeating();
        SerialCommunication::get()->getFumes();

        if(currentView == "mainMenu"){
            views[currentView]->show();
        }
    }
}