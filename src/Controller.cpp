#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>

#include "Config.h"
#include "Controller.h"
#include "CurrentState.h"
#include "SerialCommunication.h"
#include "Knob.h"
#include "views/Views.h"
#include "wifi_credentials.h"
#include "Errors.h"
#include "Debug.h"

char serverAddress[] = "192.168.0.3";  // server address
int port = 443;

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
    CurrentState::get()->setDefault();

    views["mainMenu"] = new MainMenuView();
    views["firingUp"] = new FiringUpView();
    views["hotWater"] = new HotWaterView();
    views["centralHeating"] = new CentralHeatingView();
    views["blower"] = new BlowerView();
    views["feeder"] = new FeederView();
    views["io"] = new IOView();
    views["error"] = new ErrorView();

    changeView("mainMenu");

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_AP, WIFI_PASS);

    CurrentState::get()->load();

    updateDataTimer = new Timer();
    updateDataTimer->addEventListener(this);
    updateDataTimer->start(UPDATE_DATA_TIME);
}

void Controller::changeView(String viewName, int position) {
    currentView = viewName;
    views[currentView]->reset(position);
}

void Controller::loop() {
    updateDataTimer->update();
    Knob::get()->update();
    Lcd::get()->updateView();

    SerialCommunication::get()->serialEvent();
}


void Controller::onTime(Timer* timer) {
    if (timer == updateDataTimer) {
        if (!CurrentState::get()->wifiConnected && WiFi.status() == WL_CONNECTED) {
            CurrentState::get()->wifiConnected = true;
        }

        SerialCommunication::get()->getHotWater();
        SerialCommunication::get()->getCentralHeating();
        SerialCommunication::get()->getCentralHeatingPump();
        SerialCommunication::get()->getHotWaterPump();
        SerialCommunication::get()->getFumes();
        SerialCommunication::get()->getError();

        if (CurrentState::get()->error != CentralHeating::Error::OK) {
            changeView("error");
        }

        if (DEBUG) {
            SerialCommunication::get()->getState();
        }

        if (currentView == "mainMenu" ||
            currentView == "io") {
            views[currentView]->show();
        }
    }
}