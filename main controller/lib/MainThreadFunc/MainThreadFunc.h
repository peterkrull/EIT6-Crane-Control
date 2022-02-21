#ifndef MainThreadFunc_h
#define MainThreadFunc_h

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct ConvertedData{
    short posX;
    short posY;

    int joystickX;
    int joystickY;

    float tacoX = 0;
    float tacoY = 0;

    float headAngle = 0;

    bool enableMagnet = 0;
    bool enableManual = 0;
};


short posY_Converter(int input);
short posX_Converter(int input);
float tacoX_Converter(int input);
float tacoY_Converter(int input);

struct DataOut manualControl (ConvertedData convertedData);
    
struct DataOut autonomousCountrol(ConvertedData convertedData);



//todo: make into one function
bool joystickDeadZone(float dataJoystick);
int joystickOutputFormat(float dataJoystick);
float joystick_Converter(int input);

#endif