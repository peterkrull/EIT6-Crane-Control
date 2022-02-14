#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <InputThreadFunc.h>
#include <MainThreadFunc.h>
#include <OutputThreadFunc.h>

SemaphoreHandle_t dataIn_semaphore;
SemaphoreHandle_t dataOut_semaphore;

void TaskInputThread(void *pvParameters);
void TaskMainThread(void *pvParameters);
void TaskOutputThread(void *pvParameters);


struct DataIn dataIn;
struct DataOut dataOut;


void setup(){
    Serial.begin(115200);
	Serial3.begin(115200);
	Serial.println("Serial begun");

    dataIn_semaphore = xSemaphoreCreateMutex();
	if(dataIn_semaphore != NULL) xSemaphoreGive(dataIn_semaphore);
    dataOut_semaphore = xSemaphoreCreateMutex();
    if(dataOut_semaphore != NULL) xSemaphoreGive(dataOut_semaphore);
	//Serial.println("Semaphores created");

    xTaskCreate(TaskInputThread, "InputThread",256, NULL, 1, NULL);
    xTaskCreate(TaskMainThread, "mainThread",256, NULL, 3, NULL);
    xTaskCreate(TaskOutputThread, "OutputThread",256, NULL, 2, NULL);
	
}


void loop(){
	
}


void TaskInputThread(void *pvParameters __attribute__((unused))){
	//thread timing variables
	TickType_t lastWakeTime;
	const TickType_t updateFrequency = 1; //Number of ticks between each update

	lastWakeTime = xTaskGetTickCount();

	InputPins pins;

	pinMode(pins.toggleMagnet, INPUT);
	pinMode(pins.toggleManual, INPUT);


	struct DataIn localDataIn;


	Serial.println("Input thread started");
	while(true){
		localDataIn = readInput();

		if(xSemaphoreTake(dataIn_semaphore, (TickType_t) 5) == pdTRUE){ //Checks if semaphore is free, takes semaphore if so.
			dataIn = localDataIn;

			xSemaphoreGive(dataIn_semaphore); //releases semaphore
		}
		else Serial.println("dataIn_semaphore not free, could not update");
		vTaskDelayUntil(&lastWakeTime, updateFrequency);

	}
}

void TaskMainThread(void *pvParameters __attribute__((unused))){

    struct DataIn localDataIn;
    DataOut localDataOut;
	ConvertedData convertedData;

	TickType_t lastWakeTime = xTaskGetTickCount();
	const TickType_t updateFrequency = 3; //Number of ticks between each update

	Serial.println("Main thread started");

    while(true){
        if(xSemaphoreTake(dataIn_semaphore, (TickType_t) 5) == pdTRUE){
             localDataIn = dataIn;
             xSemaphoreGive(dataIn_semaphore);
        }

		

		convertedData.joystickX = localDataIn.joystickX;
		convertedData.joystickY = localDataIn.joystickY;
		//convertedData.tacoX = taco_Converter(localDataIn.tacoX);
		//convertedData.tacoY = taco_Converter(localDataIn.tacoY);
		convertedData.posX = posX_Converter(localDataIn.posX);
		convertedData.posY = posY_Converter(localDataIn.posY);
		convertedData.toggleMagnet = localDataIn.toggleMagnet;
		convertedData.toggleManual = localDataIn.toggleManual;


        switch (dataIn.toggleManual){
			case 0:
				localDataOut = manualControl(convertedData);
				if(localDataOut.enableX == 1){
				//Serial.print("PWM x"); Serial.println(localDataOut.pwmX);
				}
				if(localDataOut.enableY == 1){
				//Serial.print("PWM y"); Serial.println(localDataOut.pwmY);
				}
				Serial.print("Angle ");Serial.println(localDataIn.headAngle);
				break;
			case 1:
				autonomousCountrol();
				Serial.println("Autonomous control");
				break;
			default:
				break;
        }

        if(xSemaphoreTake(dataOut_semaphore, (TickType_t) 5) == pdTRUE){
             dataOut = localDataOut;
             xSemaphoreGive(dataOut_semaphore);
        }
		vTaskDelayUntil(&lastWakeTime, updateFrequency);
    }
}



void TaskOutputThread(void *pvParameters __attribute__((unused))){

    DataOut localDataOut;

	TickType_t lastWakeTime = xTaskGetTickCount();
	const TickType_t updateFrequency = 3; //Number of ticks between each update

	const unsigned short pwmX = 10;
	const unsigned short pwmY = 11;
	const unsigned short enableX = 8;
	const unsigned short enableY = 9;
	const unsigned short magnetEnable = 2;
  
	pinMode(pwmX,OUTPUT);
	pinMode(pwmY,OUTPUT);
	pinMode(enableX,OUTPUT);
	pinMode(enableY,OUTPUT);
	pinMode(magnetEnable,OUTPUT);

	Serial.println("Output thread started");
    while (true)
    {
        if(xSemaphoreTake(dataOut_semaphore, (TickType_t) 5) == pdTRUE){
			localDataOut = dataOut;
			xSemaphoreGive(dataOut_semaphore);
        }

		String magnetOn = String("M" + String(localDataOut.magnetEnable));
		//Serial.print("enableX");Serial.println(localDataOut.enableX);		
		//Serial.print("enableY");Serial.println(localDataOut.enableY);
		//Serial.print("pwmX");Serial.println(localDataOut.pwmX);
		//Serial.print("pwmY");Serial.println(localDataOut.pwmY);
		//Serial.print("enableMagnet");Serial.println(localDataOut.magnetEnable);
		//Serial.print(magnetOn);

		analogWrite(pwmX,localDataOut.pwmX);
		analogWrite(pwmY,localDataOut.pwmY);
		digitalWrite(enableX,localDataOut.enableX);
		digitalWrite(enableY,localDataOut.enableY);
		digitalWrite(magnetEnable,localDataOut.magnetEnable);
		Serial3.println(magnetOn);

		vTaskDelayUntil(&lastWakeTime, updateFrequency);
    }
}
