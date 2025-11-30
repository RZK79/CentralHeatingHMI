#ifndef _VIEW_H_
#define _VIEW_H_

#include "Lcd.h"
#include "SerialCommunication.h"

class Controller;

class View {
protected:    
    Controller* parentController;
public:
    View(Controller* parent);    
    virtual void show() = 0;
    virtual void reset(int position = 0) = 0;
};

#endif