#ifndef inputThread_h
#define inputThread_h

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


struct DataIn{
    float posX = 0;
    float posY = 0;
    float tacoX = 0;
    float tacoY = 0;
    int joystickX = 0;
    int joystickY = 0;
    bool toggleMagnet = 0;
    bool toggleManual = 0;
    unsigned long measurementTime = 0;
};


#endif