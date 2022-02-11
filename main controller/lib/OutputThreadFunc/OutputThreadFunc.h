#ifndef OutputThreadFunc_h
#define OutputThreadFunc_h

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct DataOut{
  int pwmX = 0;
  int pwmY = 0;
  bool enableX = 0;
  bool enableY = 0;
};

#endif