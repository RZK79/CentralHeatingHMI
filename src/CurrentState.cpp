#include "CurrentState.h"

bool CurrentState::isOn = false;
bool CurrentState::isCentralHeatingPumpOn = false;
bool CurrentState::isHotWaterPumpOn = false;
int CurrentState::feederTimeToSet = 1000;
int CurrentState::feederPeriodToSet = 1000;
int CurrentState::centralHeatingTemperatureToSet = 55;
int CurrentState::centralHeatingTemperature = 0;
int CurrentState::hotWaterTemperatureToSet = 45;
int CurrentState::hotWaterTemperature = 0;
int CurrentState::blowerSpeedToSet = 750;
int CurrentState::fumesTemperature = 0;