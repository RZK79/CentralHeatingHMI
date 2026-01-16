#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "DataSender.h"
#include "Config.h"
#include "Controller.h"

extern char serverAddress[];

DataSender::DataSender() {
    timer = new Timer();
    timer->addEventListener(this);
    timer->start(10 * SECOND);
}

void DataSender::onTime(Timer *t){
    if (WiFi.status() == WL_CONNECTED) {
        send();
    }
}

void DataSender::update(){
    timer->update();
}

void DataSender::send() {
    /*
    char buf[200];
    sprintf(buf,
        "{                  \
            \"cht\":%d,   \
            \"hwt\":%d,   \
            \"ft\":%d     \
        }",
        Controller::get()->getCurrentState()->centralHeatingTemperature,
        Controller::get()->getCurrentState()->hotWaterTemperature,
        Controller::get()->getCurrentState()->fumesTemperature
    );
    */
    WiFiClient client;
    HTTPClient http;
    char server[200];
    sprintf(server, "%sstore.php?cht=%d&hwt=%d&ft=%d", serverAddress, Controller::get()->getCurrentState()->centralHeatingTemperature, Controller::get()->getCurrentState()->hotWaterTemperature, Controller::get()->getCurrentState()->fumesTemperature);
    http.begin(client, server);
    http.GET();
    http.end();
}