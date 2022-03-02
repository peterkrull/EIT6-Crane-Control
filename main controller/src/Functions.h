#ifndef manuelFunctions_h
#define manuelFunctions_h

#include <Arduino.h>

bool joystickDeadZone(float dataJoystick);
int joystickOutputFormat(float dataJoystick);
int endstop(int pwm, float min, float max, float pos);
int8_t currentToPwm(float current);

#endif