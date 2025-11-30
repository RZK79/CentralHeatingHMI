#include "SerialCommunication.h"
#include "CurrentState.h"
#include "Controller.h"

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
    Serial.print("*gfu#");
}

void SerialCommunication::getCentralHeatingPump() {
    Serial.print("*gchp#");
}

void SerialCommunication::getHotWaterPump() {
    Serial.print("*ghwp#");
}

void SerialCommunication::getLighter() {
    Serial.print("*gl#");
}

void SerialCommunication::getBlowerSpeed() {
    Serial.print("*gbs#");
}

void SerialCommunication::getFeeder() {
    Serial.print("*gf#");
}

void SerialCommunication::getState() {
    Serial.print("*gs#");
}

void SerialCommunication::getError() {
    Serial.print("*error#");
}

void SerialCommunication::reset() {
    data[0] = '\0';
    recvInProgress = false;
    i = 0;
}

void SerialCommunication::serialEvent() {
    if (Serial.available()) {
        while (Serial.available() > 0) {
            char c = Serial.read();
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
}

void SerialCommunication::parseData(char* data) {
    if (strcmp(data, "gfu") == 0) {
        controller->getCurrentState()->fumesTemperature = atoi(&data[3]);
    } else if (strcmp(data, "ghw") == 0) {
        controller->getCurrentState()->hotWaterTemperature = atoi(&data[3]);
    } else if (strcmp(data, "gch") == 0) {
        controller->getCurrentState()->centralHeatingTemperature = atoi(&data[3]);
    } else if (strcmp(data, "gchp") == 0) {
        controller->getCurrentState()->isCentralHeatingPumpOn = (bool)atoi(&data[4]);
    } else if (strcmp(data, "ghwp") == 0) {
        controller->getCurrentState()->isHotWaterPumpOn = (bool)atoi(&data[4]);
    } else if (strcmp(data, "gl") == 0) {
        controller->getCurrentState()->lighter = (bool)atoi(&data[2]) == 0 ? false : true;
    } else if (strcmp(data, "gbs") == 0) {
        int speed = 6;
        switch (atoi(&data[3])) {
            default:
            case 6:
                speed = 0;
                break;

            case 0:
                speed = 3600;
                break;

            case 1:
                speed = 3000;
                break;

            case 2:
                speed = 2500;
                break;

            case 3:
                speed = 2000;
                break;

            case 4:
                speed = 1500;
                break;

            case 5:
                speed = 1000;
                break;
        }
        controller->getCurrentState()->blowerSpeed = speed;
    } else if (strcmp(data, "gf") == 0) {
        controller->getCurrentState()->isFeederOn = (bool)atoi(&data[2]);
    } else if (strcmp(data, "gs") == 0) {
        // Debug::state = (ControllerState)atoi(&data[2]);
    } else if (strcmp(data, "error") == 0) {
        controller->getCurrentState()->error = atoi(&data[5]);
    }
}