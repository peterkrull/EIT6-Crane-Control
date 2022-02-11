#include <inputThread.cpp>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <formatThread.cpp>

struct DataOut{
  int pwmX;
  int pwmY;
};

DataOut dataOut;

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

	xTaskCreate(TaskReadInput, "Output",128, NULL, 1, NULL);
}

void loop() {
}

void TaskOutput(){
  const unsigned short pwmX = 10;
  const unsigned short pwmY = 11;
  const unsigned short enableX = 8;
  const unsigned short enableY = 9;
  
  pinMode(pwmX,OUTPUT);
  pinMode(pwmY,OUTPUT);
  pinMode(enableX,OUTPUT);
  pinMode(enableY,OUTPUT);

  while (true){
    analogWrite(pwmX,)
  }
  
}