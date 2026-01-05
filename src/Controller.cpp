#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <Esp.h>
#include "Controller.h"
#include "Config.h"
#include "CurrentState.h"
#include "Debug.h"
#include "Errors.h"
#include "Knob.h"
#include "SerialCommunication.h"
#include "views/Views.h"
#include "wifi_credentials.h"

char serverAddress[] = "192.168.0.3"; // server address
int port = 443;

Controller* Controller::instance = nullptr;

Controller* Controller::get()
{
    if (instance == nullptr) {
        instance = new Controller();
    }

    return instance;
}

Controller::Controller()
{
    state = new CurrentState();
    se = new SerialCommunication();
    se->resetArduino();

    views["mainMenu"] = new MainMenuView();
    views["firingUp"] = new FiringUpView();
    views["hotWater"] = new HotWaterView();
    views["centralHeating"] = new CentralHeatingView();
    views["blower"] = new BlowerView();
    views["feeder"] = new FeederView();
    views["io"] = new IOView();
    views["settings"] = new SettingsView();
    views["error"] = new ErrorView();
    views["NTC"] = new NTCView();
    views["timing"] = new TimingView();
}

void Controller::setup()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_AP, WIFI_PASS);

    state->load();

    updateDataTimer = new Timer();
    updateDataTimer->addEventListener(this);
    updateDataTimer->start(UPDATE_DATA_TIME);

    updateTempTimer = new Timer();
    updateTempTimer->addEventListener(this);
    updateTempTimer->start(UPDATE_TEMPERATURE_TIME);

    changeView("mainMenu");
}

void Controller::updateParameters()
{
    se->setCentralHeatingTemperature(state->centralHeatingTemperatureToSet);
    se->setHotWaterTemperature(state->hotWaterTemperatureToSet);
    se->setFeederPeriod(state->feederPeriodToSet);
    se->setFeederTime(state->feederTimeToSet);
    se->setBlowerSpeedFiringUp(state->blowerSpeedToSetFiringUp);
    se->setBlowerSpeedStabilization(state->blowerSpeedToSetStabilization);
    se->setBlowerSpeedNormal(state->blowerSpeedToSetNormal);
    se->setNTCCHType(state->NTCch);
    se->setNTCHWType(state->NTChw);
}

void Controller::changeView(String viewName, int position)
{
    updateParameters();
    currentView = viewName;
    views[currentView]->reset(position);
}

CurrentState* Controller::getCurrentState()
{
    return state;
}

SerialCommunication* Controller::getSerialCommunication()
{
    return se;
}

void Controller::loop()
{
    updateDataTimer->update();
    updateTempTimer->update();
    Knob::get()->update();
    Lcd::get()->updateView();
}

void Controller::onTime(Timer* timer)
{
    if (timer == updateDataTimer) {
        se->getCentralHeatingPump();
        se->getHotWaterPump();
        se->getFeeder();
        se->getLighter();
        se->getBlowerSpeed();

        se->getError();
    } else if (timer == updateTempTimer) {
        se->serialEvent();
        se->getHotWaterTemperature();
        se->getFumesTemperature();
        se->getCentralHeatingTemperature();

        if (!state->wifiConnected && WiFi.status() == WL_CONNECTED) {
            state->wifiConnected = true;
        }

        if (state->error != CentralHeating::Errors::OK) {
            changeView("error");
        }

        if (currentView == "mainMenu" || currentView == "io") {
            views[currentView]->show();
        }
    }
}

void Controller::reset()
{
    se->resetArduino();
    EspClass::reset();
}
