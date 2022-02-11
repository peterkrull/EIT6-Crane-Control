#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <InputThreadFunc.h>
#include <MainThreadFunc.h>
#include <OutputThreadFunc.h>

SemaphoreHandle_t dataIn_semaphore;
SemaphoreHandle_t dataOut_semaphore;

void TaskInputThread(void *pvParameters);


DataIn dataIn;
DataOut dataOut;


void setup(){
    Serial.begin(9600);
	Serial3.begin(9600);

    dataIn_semaphore = xSemaphoreCreateMutex();
	if(dataIn_semaphore != NULL) xSemaphoreGive(dataIn_semaphore);
    dataOut_semaphore = xSemaphoreCreateMutex();
    if(dataOut_semaphore != NULL) xSemaphoreGive(dataOut_semaphore);


    xTaskCreate(TaskInputThread, "InputThread",128, NULL, 3, NULL);
    xTaskCreate(TaskMainThread, "mainThread",128, NULL, 2, NULL);
    xTaskCreate(TaskOutputThread, "OutputThread",128, NULL, 1, NULL);
}


void loop();


void TaskInputThread(void *pvParameters __attribute__((unused))){
	const unsigned short toggleMagnet_pin = 2;
	const unsigned short toggleManual_pin = 3;

	const unsigned short joystickX_pin = 8;
	const unsigned short joystickY_pin = 9;
	const unsigned short posX_pin = 0;
	const unsigned short posY_pin = 1;
	const unsigned short tacoX_pin = 2;
	const unsigned short tacoY_pin = 3;
	
	//thread timing variables
	TickType_t lastWakeTime;
	const TickType_t updateFrequency = 1; //Number of ticks between each update

	lastWakeTime = xTaskGetTickCount();


	while(true){
		bool toggleMagnet_bool = digitalRead(toggleMagnet_pin);
		bool toggleManual_bool = digitalRead(toggleManual_pin);
		short joystickX_voltage = analogRead(joystickX_pin);
		short joystickY_voltage = analogRead(joystickY_pin);
		//short tacoX_voltage = analogRead(tacoX_pin);
		//short tacoY_voltage = analogRead(tacoY_pin);
		short posX_voltage = analogRead(posX_pin);
		short posY_voltage = analogRead(posY_pin);

		
		float joystickX = joystick_Converter(joystickX_voltage);
		float joystickY = joystick_Converter(joystickY_voltage);
		//float tacoX = taco_Converter(tacoX_voltage);
		//float tacoY = taco_Converter(tacoY_voltage);
		short posX = posX_Converter(posX_voltage);
		short posY = posY_Converter(posY_voltage);
		unsigned long measurementTime = millis();
		Serial.println(measurementTime);

		if(xSemaphoreTake(dataIn_semaphore, (TickType_t) 5) == pdTRUE){ //Checks if semaphore is free, releases semaphore if so.
			dataIn.toggleMagnet = toggleMagnet_bool;
			dataIn.toggleManual = toggleManual_bool;
			dataIn.joystickX = joystickX;
			dataIn.joystickY = joystickY;
			//dataIn.tacoX = tacoX;
			//dataIn.tacoY = tacoY;
			dataIn.posX = posX;
			dataIn.posY = posY;
			dataIn.measurementTime = measurementTime;

			xSemaphoreGive(dataIn_semaphore);
		}
		else Serial.println("dataIn_semaphore not free, could not update");
		vTaskDelayUntil(&lastWakeTime, updateFrequency);
	}
}

void TaskMainThread(void *pvParameters __attribute__((unused))){

    DataIn localDataIn;
    DataOut localDataOut;

    while(true){

        if(xSemaphoreTake(dataIn_semaphore, (TickType_t) 5) == pdTRUE){
             localDataIn = dataIn;
             xSemaphoreGive(dataIn_semaphore);
        }

        switch (dataIn.toggleManual)
        {
        case 1:
            manualControl();
            break;
        case 0:
            autonomousCountrol();
            break
        default:
            break;
        }

        if(xSemaphoreTake(dataOut_semaphore, (TickType_t) 5) == pdTRUE){
             localDataOut = dataOut;
             xSemaphoreGive(dataOut_semaphore);
        }
    }
    

}

void TaskOutputThread(void *pvParameters __attribute__((unused))){

    DataOut localDataOut;
    while (true)
    {
        
        if(xSemaphoreTake(dataOut_semaphore, (TickType_t) 5) == pdTrue){
            dataFormat.deadZoneEnableX = deadZone(dataIn.joystickX);
            dataFormat.deadZoneEnableY = deadZone(dataIn.joystickY);
            dataFormat.joystickX = joystickFormat(dataIn.joystickX);
            dataFormat.joystickY = joystickFormat(dataIn.joystickY);
        }
    }
}
