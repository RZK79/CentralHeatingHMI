#include "SerialCommunication.h"
#include "Controller.h"
#include "CurrentState.h"

SerialCommunication::SerialCommunication()
{
    Serial.begin(9600);
    init();
}

void SerialCommunication::init()
{
    data[0] = '\0';
    recvInProgress = false;
    i = 0;
}

void SerialCommunication::serialEvent()
{
    while(Serial.available()){
        char c = Serial.read();
        if (recvInProgress) {
            if (c != end) {
                data[i++] = c;
                if (i >= 32) {
                    i = 31;
                }
            } else {
                data[i] = '\0';
                recvInProgress = false;
                i = 0;
                parseData(data);
            }
        } else if (c == start) {
            init();
            recvInProgress = true;
        }
    }
}

void SerialCommunication::parseData(char* data)
{
    if (strncmp("gft", data, 3) == 0) {
        Controller::get()->getCurrentState()->fumesTemperature = atoi(&data[3]);
    } else if (strncmp("ghwt", data, 4) == 0) {
        Controller::get()->getCurrentState()->hotWaterTemperature = atoi(&data[4]);
    } else if (strncmp("gcht", data, 4) == 0) {
        Controller::get()->getCurrentState()->centralHeatingTemperature = atoi(&data[4]);
    } else if (strncmp("gchp", data, 4) == 0) {
        Controller::get()->getCurrentState()->isCentralHeatingPumpOn = (bool)atoi(&data[4]);
    } else if (strncmp("ghwp", data, 4) == 0) {
        Controller::get()->getCurrentState()->isHotWaterPumpOn = (bool)atoi(&data[4]);
    } else if (strncmp("gl", data, 2) == 0) {
        Controller::get()->getCurrentState()->lighter = (bool)atoi(&data[2]) == 0 ? false : true;
    } else if (strncmp("gbs", data, 3) == 0) {
        Controller::get()->getCurrentState()->blowerSpeed = atoi(&data[3]);
    } else if (strncmp("gf", data, 2) == 0) {
        Controller::get()->getCurrentState()->isFeederOn = (bool)atoi(&data[2]);
    } else if (strncmp("error", data, 5) == 0) {
        Controller::get()->getCurrentState()->error = atoi(&data[5]);
    }
}

void SerialCommunication::turnOn()
{
    Serial.print("*ton#");
}

void SerialCommunication::turnOff()
{
    Serial.print("*toff#");
}

void SerialCommunication::setFeederTime(int time)
{
    Serial.print("*sft");
    Serial.print(time);
    Serial.print("#");
}

void SerialCommunication::setFeederPeriod(int time)
{
    Serial.print("*sfp");
    Serial.print(time);
    Serial.print("#");
}

void SerialCommunication::setBlowerSpeedFiringUp(int speed)
{
    Serial.print("*sbsfu");
    Serial.print(speed);
    Serial.print("#");
}

void SerialCommunication::setBlowerSpeedStabilization(int speed)
{
    Serial.print("*sbss");
    Serial.print(speed);
    Serial.print("#");
}

void SerialCommunication::setBlowerSpeedNormal(int speed)
{
    Serial.print("*sbsn");
    Serial.print(speed);
    Serial.print("#");
}

void SerialCommunication::setCentralHeatingTemperature(int temperature)
{
    Serial.print("*scht");
    Serial.print(temperature);
    Serial.print("#");
}

void SerialCommunication::getCentralHeatingTemperature()
{
    Serial.print("*gcht#");
}

void SerialCommunication::setHotWaterTemperature(int temperature)
{
    Serial.print("*shwt");
    Serial.print(temperature);
    Serial.print("#");
}

void SerialCommunication::getHotWaterTemperature()
{
    Serial.print("*ghwt#");
}

void SerialCommunication::getFumesTemperature()
{
    Serial.print("*gft#");
}

void SerialCommunication::getCentralHeatingPump()
{
    Serial.print("*gchp#");
}

void SerialCommunication::getHotWaterPump()
{
    Serial.print("*ghwp#");
}

void SerialCommunication::getLighter()
{
    Serial.print("*gl#");
}

void SerialCommunication::getBlowerSpeed()
{
    Serial.print("*gbs#");
}

void SerialCommunication::getFeeder()
{
    Serial.print("*gf#");
}

void SerialCommunication::getError()
{
    Serial.print("*error#");
}

void SerialCommunication::resetError()
{
    Serial.print("*reseterror#");
}

void SerialCommunication::resetArduino()
{
    Serial.print("*reset#");
}

void SerialCommunication::setNTCCHType(int ntcType)
{
    Serial.print("*sntcch");
    Serial.print(ntcType);
    Serial.print("#");
}

void SerialCommunication::setNTCHWType(int ntcType)
{
    Serial.print("*sntchw");
    Serial.print(ntcType);
    Serial.print("#");
}

void SerialCommunication::turnCentralHeatingPumpOn()
{
    Serial.print("*chpumpon#");
}

void SerialCommunication::turnCentralHeatingPumpOff()
{
    Serial.print("*chpumpoff#");
}

void SerialCommunication::turnHotWaterPumpOn()
{
    Serial.print("*hwpumpon#");
}

void SerialCommunication::turnHotWaterPumpOff()
{
    Serial.print("*hwpumpoff#");
}

void SerialCommunication::setFiringUpTime(int time)
{
    Serial.print("*sfut");
    Serial.print(time);
    Serial.print("#");
}

void SerialCommunication::setStabilizationTime(int time)
{
    Serial.print("*sst");
    Serial.print(time);
    Serial.print("#");
}
