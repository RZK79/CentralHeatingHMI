#ifndef _VIEWS_H_
#define _VIEWS_H_

#include <Arduino.h>
#include "views/MainMenuView.h"
#include "views/FiringUpView.h"
#include "views/HotWaterView.h"
#include "views/CentralHeatingView.h"
#include "views/BlowerView.h"
#include "views/FeederView.h"
#include "views/IOView.h"

String viewsNames[] = {
    "meinMenu"
    "firingUp",
    "hotWater",
    "centralHeating",
    "blower",
    "feeder",
    "io"
};

#endif