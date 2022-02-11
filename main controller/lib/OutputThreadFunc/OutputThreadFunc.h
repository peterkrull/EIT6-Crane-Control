#ifndef OutputThreadFunc_h
#define OutputThreadFunc_h

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct DataOut{
    int joystickX = 0;
    int joystickY = 0;
    bool deadZoneEnableX = 0;
    bool deadZoneEnableY = 0 

};


#endif