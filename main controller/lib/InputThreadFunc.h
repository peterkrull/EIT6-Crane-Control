#ifndef inputThread_h
#define inputThread_h

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

short posY_Converter(int input);

short posX_Converter(int input);

float joystick_Converter(int input);



#endif