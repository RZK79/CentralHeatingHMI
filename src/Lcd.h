#ifndef _LCD_H_
#define _LCD_H_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Lcd{
    static Lcd *instance;
    Adafruit_SSD1306 *display;
    bool viewUpdated;
    Lcd();
public:
    static Lcd* get();
    Adafruit_SSD1306 *screen();
    void invalidateView();
    void updateView();
};

#endif