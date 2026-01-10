#include <ArduinoHttpClient.h>
#include "DataSender.h"
#include "Config.h"
#include "Controller.h"

DataSender::DataSender()
{
    timer = new Timer();
    timer->addEventListener(this);
    timer->start(10 * SECOND);
}

void DataSender::send(){
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

    
}