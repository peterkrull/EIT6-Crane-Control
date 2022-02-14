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
    float headAngle = 0;
};

struct InputPins{
    const unsigned short toggleMagnet = 2;
	const unsigned short toggleManual = 3;

	const unsigned short joystickX = 8;
	const unsigned short joystickY = 9;
	const unsigned short posX = 0;
	const unsigned short posY = 1;
	const unsigned short tacoX = 2;
	const unsigned short tacoY= 3;
};

struct DataIn readInput(void);


#endif