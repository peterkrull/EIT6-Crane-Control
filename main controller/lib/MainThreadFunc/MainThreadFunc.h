#ifndef MainThreadFunc_h
#define MainThreadFunc_h

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct ConvertedData{
    short posX;
    short posY;
    float joystickX;
    float joystickY;

    bool magnet;
};


short posY_Converter(int input);
short posX_Converter(int input);


void manualControl ();
    
void autonomousCountrol();



//todo: make into one function
bool joystickDeadZone(float dataJoystick);
int joystickOutputFormat(float dataJoystick);
float joystick_Converter(int input);

#endif