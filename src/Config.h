#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>

#define SECOND (uint16_t)1000
#define MINUTE (uint16_t)60*SECOND

#define ENCODER_A       D3
#define ENCODER_B       D6
#define BUTTON          D5
#define LCD_SDA         SDA
#define LCD_SCK         SCL

#define UPDATE_DATA_TIME 500
#define UPDATE_TEMPERATURE_TIME 500

#endif