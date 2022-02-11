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
	Serial3.begin(9600);
	dataIn_semaphore = xSemaphoreCreateMutex();
	if(dataIn_semaphore != NULL) xSemaphoreGive(dataIn_semaphore);

	xTaskCreate(TaskReadInput, "readInput",128, NULL, 1, NULL);
}

void loop() {
}

void TaskOutput(){
  
  const unsigned short pwmX = 41;
  const unsigned short pwmY = 42;
  const unsigned short enableX = 39;
  const unsigned short enableY = 40;

  pinMode(pwmX,OUTPUT);
  pinMode(pwmY,OUTPUT);
  pinMode(enableX,OUTPUT);
  pinMode(enableY,OUTPUT);
}