#include <inputThread.cpp>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

struct DataFormat{
    int joystickXformat = 0;
    int joystickYformat = 0;
    bool deadZoneEnableX = 0;
    bool deadZoneEnableY = 0 

};

DataFormat dataFormat;

void setup()
{
	Serial.begin(9600);
	Serial3.begin(9600);
	dataIn_semaphore = xSemaphoreCreateMutex();
	if(dataIn_semaphore != NULL) xSemaphoreGive(dataIn_semaphore);

	xTaskCreate(TaskReadInput, "readInput",128, NULL, 1, NULL);

}

void loop(){

}

void TaskFormatData(){
    while (true)
    {
        /* code */
    }
    
}


void FormatJoystickDataX(float dataJoystickX){
    bool toReturn;
    if(-5 < dataIn.joystickX < 5){
        toReturn = 1;
    }
    else{
        toReturn = 0;
    }

    Xformat = dataIn.joystickX 
    return toReturn;
}

void FormatJoystickDataY(float dataJoystickY){


    if (-5 < dataIn.joystickY < 5)
    {
        dataFormat.deadZoneEnabley = 1;
    }
    return toReturn;
}