#include "SerialCommunication.h"
#include "CurrentState.h"

SerialCommunication* SerialCommunication::instance = nullptr;

SerialCommunication* SerialCommunication::get() {
    if (SerialCommunication::instance == nullptr) {
        SerialCommunication::instance = new SerialCommunication();
    }

    return SerialCommunication::instance;
}

SerialCommunication::SerialCommunication() {
    Serial.begin(9600);
}

void SerialCommunication::turnOn() {
    Serial.print("*ton#");
}

void SerialCommunication::turnOff() {
    Serial.print("*toff#");
}

void SerialCommunication::setFeederTime(int time) {
    Serial.print("*sft");
    Serial.print(time);
    Serial.print("#");
}

void SerialCommunication::setFeederPeriod(int time) {
    Serial.print("*sfp");
    Serial.print(time);
    Serial.print("#");
}

void SerialCommunication::setBlower(int speed) {
    Serial.print("*sb");
    Serial.print(speed);
    Serial.print("#");
}

void SerialCommunication::setCentralHeating(int temperature) {
    Serial.print("*sch");
    Serial.print(temperature);
    Serial.print("#");
}

void SerialCommunication::getCentralHeating() {
    Serial.print("*gch#");
}

void SerialCommunication::setHotWater(int temperature) {
    Serial.print("*shw");
    Serial.print(temperature);
    Serial.print("#");
}

void SerialCommunication::getHotWater() {
    Serial.print("*ghw#");
}

void SerialCommunication::getFumes() {
    Serial.print("*gf#");
}

void SerialCommunication::getCentralHeatingPump() {
    Serial.print("*gchp#");
}

void SerialCommunication::getHotWaterPump() {
    Serial.print("*ghwp#");
}


void SerialCommunication::reset() {
    data[0] = '\0';
    recvInProgress = false;
    i = 0;
}

void SerialCommunication::serialEvent() {
    char c;

    while (Serial.available() > 0) {
        c = Serial.read();
        if (SerialCommunication::recvInProgress) {
            if (c != SerialCommunication::end) {
                SerialCommunication::data[i++] = c;
                if (i >= 32) {
                    i = 31;
                }
            } else {
                SerialCommunication::data[i] = '\0';
                parseData(data);
                reset();
            }
        } else if (c == SerialCommunication::start) {
            recvInProgress = true;
        }
    }
}

void SerialCommunication::parseData(char* data) {
    if (strstr(data, "gf") != NULL) {
        CurrentState::get()->fumesTemperature = atoi(&data[2]);
    } else if (strstr(data, "ghw") != NULL) {
        CurrentState::get()->hotWaterTemperature = atoi(&data[3]);
    } else if (strstr(data, "gch") != NULL) {
        CurrentState::get()->centralHeatingTemperature = atoi(&data[3]);
    } else if (strstr(data, "gchp") != NULL) {
        CurrentState::get()->isCentralHeatingPumpOn = (bool)atoi(&data[4]);
    } else if (strstr(data, "ghwp") != NULL) {
        CurrentState::get()->isHotWaterPumpOn = (bool)atoi(&data[4]);
    }
}