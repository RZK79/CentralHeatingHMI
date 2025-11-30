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

Controller::Controller() {
    state = new CurrentState();
    se = new SerialCommunication();

    views["mainMenu"] = new MainMenuView(this);
    views["firingUp"] = new FiringUpView(this);
    views["hotWater"] = new HotWaterView(this);
    views["centralHeating"] = new CentralHeatingView(this);
    views["blower"] = new BlowerView(this);
    views["feeder"] = new FeederView(this);
    views["io"] = new IOView(this);
    views["error"] = new ErrorView(this);
}

void Controller::setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_AP, WIFI_PASS);

    state->load();

    updateDataTimer = new Timer();
    updateDataTimer->addEventListener(this);
    updateDataTimer->start(UPDATE_DATA_TIME);

    changeView("mainMenu");
}

void Controller::changeView(String viewName, int position) {
    currentView = viewName;
    views[currentView]->reset(position);
}

CurrentState* Controller::getCurrentState() {
    return state;
}

SerialCommunication* Controller::getSerialCommunication() {
    return se;
}

void Controller::loop() {
    updateDataTimer->update();
    Knob::get()->update();
    Lcd::get()->updateView();

    se->serialEvent();
}


void Controller::onTime(Timer* timer) {
    if (timer == updateDataTimer) {
        if (!state->wifiConnected && WiFi.status() == WL_CONNECTED) {
            state->wifiConnected = true;
        }

        se->getHotWater();
        se->getCentralHeating();
        se->getCentralHeatingPump();
        se->getHotWaterPump();
        se->getFumes();
        se->getError();

        if (state->error != CentralHeating::Errors::OK) {
            changeView("error");
        }

        if (DEBUG) {
            se->getState();
        }

        if (currentView == "mainMenu" ||
            currentView == "io") {
            views[currentView]->show();
        }
    }
}

Controller* controller = new Controller();
