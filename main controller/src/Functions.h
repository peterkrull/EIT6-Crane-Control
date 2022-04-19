#ifndef manuelFunctions_h
#define manuelFunctions_h

#include <Arduino.h>

bool joystickDeadZone(float dataJoystick);
int joystickOutputFormat(float dataJoystick);
int endstop(int pwm, float min, float max, float pos);
uint8_t currentToPwm(double current, bool magnetSw, float xSpeed, float ySpeed, bool axis);
uint8_t currentToPwmX(double current, float xSpeed, bool* enableXMotor);
void turnOnElectromagnet(bool status, int LEDPin);
#endif