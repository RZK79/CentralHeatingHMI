#include "DataSender.h"
#include "Config.h"
#include "Controller.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

extern char serverAddress[];

DataSender::DataSender()
{
    timer = new Timer();
    timer->addEventListener(this);
    timer->start(5 * 1000);
}

void DataSender::onTime(Timer* t)
{
    if (WiFi.status() == WL_CONNECTED) {
        send();
    }
}

void DataSender::update()
{
    timer->update();
}

void DataSender::send()
{

    char url[256];
    sprintf(url, "%sstore.php", serverAddress);

    char payload[1024];
    memset(payload, 1, 1024);
    sprintf(payload,
        "{                \
            \"cht\":%d,   \
            \"hwt\":%d,   \
            \"ft\":%d,    \
            \"pumpch\":%d,  \
            \"pumphw\":%d,  \
            \"status\":%d   \
        }",
        Controller::get()->getCurrentState()->centralHeatingTemperature,
        Controller::get()->getCurrentState()->hotWaterTemperature,
        Controller::get()->getCurrentState()->fumesTemperature,
        Controller::get()->getCurrentState()->isCentralHeatingPumpOn,
        Controller::get()->getCurrentState()->isHotWaterPumpOn,
        Controller::get()->getCurrentState()->currentState);

    WiFiClient client;
    HTTPClient http;

    if (WiFi.status() == WL_CONNECTED) {
        http.begin(client, url);
        http.addHeader("Content-Type", "application/json");
        Serial.println();
        Serial.println(payload);
        int httpCode = http.POST((const uint8_t*)payload, strlen(payload));
        if (httpCode == HTTP_CODE_OK) {
            const String& payload = http.getString();
            Serial.println("received payload:\n<<");
            Serial.println(payload);
            Serial.println(">>");
        }
        Serial.println();
        http.end();
    }
}