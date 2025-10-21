#include <Arduino.h>
#include "Controller.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Start");

    Controller::get()->setup();
}

void loop() {
    Controller::get()->loop();
}
