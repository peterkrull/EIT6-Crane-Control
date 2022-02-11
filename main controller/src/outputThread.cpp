#include <inputThread.cpp>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct DataOut{

};


//Inputs
int motorX;
int motorY;
bool enableX;
bool enableY;



void setup() {
  Serial.begin(9600);
  pinMode(pwmX,OUTPUT);
  pinMode(pwmY,OUTPUT);
  pinMode(enableX,OUTPUT);
  pinMode(enableY,OUTPUT);
}

void loop() {
}

void TaskOutput(){
  const unsigned short pwmX = 41;
  const unsigned short pwmY = 42;
  const unsigned short enableX = 39;
  const unsigned short enableY = 40;

  
}