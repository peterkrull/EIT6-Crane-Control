#include <inputThread.cpp>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

/*
struct DataOut{
    int joystickX = 0;
    int joystickY = 0;
    bool deadZoneEnableX = 0;
    bool deadZoneEnableY = 0 

};
*/

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
        dataFormat.deadZoneEnableX = deadZone(dataIn.joystickX);
        dataFormat.deadZoneEnableY = deadZone(dataIn.joystickY);
        dataFormat.joystickX = joystickFormat(dataIn.joystickX);
        dataFormat.joystickY = joystickFormat(dataIn.joystickY);
    }
}

void joystickDeadZone(float dataJoystick){
    bool toReturn;
    if(-5 < dataJoystick < 5){
        toReturn = 1;
    }
    else{
        toReturn = 0;
    }
    return toReturn;
}

void joystickFormat(float dataJoystick){
    int toReturn = int(1.015*dataJoystick+127.5);
    return toReturn;
}