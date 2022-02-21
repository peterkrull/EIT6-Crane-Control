#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <InputThreadFunc.h>
#include <MainThreadFunc.h>
#include <OutputThreadFunc.h>


SemaphoreHandle_t dataIn_semaphore;
SemaphoreHandle_t dataOut_semaphore;
SemaphoreHandle_t serial3_semaphore;


void TaskInputThread(void *pvParameters);
void TaskMainThread(void *pvParameters);
void TaskOutputThread(void *pvParameters);


struct DataIn dataIn;
struct DataOut dataOut;



void setup(){
	
    Serial.begin(115200);
	Serial3.begin(9600);
	if(Serial3.available()>0) Serial3.readString();
	
	Serial.println("Serial begun");
	Serial.print("tickConfig ");Serial.println(configTICK_RATE_HZ);

    dataIn_semaphore = xSemaphoreCreateMutex();
	if(dataIn_semaphore != NULL) xSemaphoreGive(dataIn_semaphore);
    dataOut_semaphore = xSemaphoreCreateMutex();
    if(dataOut_semaphore != NULL) xSemaphoreGive(dataOut_semaphore);
	serial3_semaphore = xSemaphoreCreateMutex();
    if(serial3_semaphore != NULL) xSemaphoreGive(serial3_semaphore);
	//Serial.println("Semaphores created");

    xTaskCreate(TaskInputThread, "InputThread",2048, NULL, 3, NULL);
    xTaskCreate(TaskMainThread, "mainThread",512, NULL, 2, NULL);
    xTaskCreate(TaskOutputThread, "OutputThread",512, NULL, 1, NULL);
	
}


void loop(){
	
}


void TaskInputThread(void *pvParameters __attribute__((unused))){
	//thread timing variables
	TickType_t lastWakeTime;
	const TickType_t updateFrequency = 1; //Number of ticks between each update

	lastWakeTime = xTaskGetTickCount();

	InputPins pins;

	pinMode(pins.enableMagnet, INPUT);
	pinMode(pins.enableManual, INPUT);


	struct DataIn localDataIn;


	Serial.println("Input thread started");
	vTaskDelay(1);
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
	const TickType_t updateFrequency = 1; //Number of ticks between each update

	Serial.println("Main thread started");

	vTaskDelay(1);

    while(true){
		int prev_time = localDataIn.measurementTime;
        if(xSemaphoreTake(dataIn_semaphore, (TickType_t) 5) == pdTRUE){
             localDataIn = dataIn;
             xSemaphoreGive(dataIn_semaphore);
        }

		Serial.print("delta_time: "); Serial.println(localDataIn.measurementTime-prev_time);		

		convertedData.joystickX = localDataIn.joystickX;
		convertedData.joystickY = localDataIn.joystickY;
		//convertedData.tacoX = tacoX_Converter(localDataIn.tacoX);
		//convertedData.tacoY = tacoY_Converter(localDataIn.tacoY);
		convertedData.posX = posX_Converter(localDataIn.posX);
		convertedData.posY = posY_Converter(localDataIn.posY);
		convertedData.enableMagnet = localDataIn.enableMagnet;
		convertedData.enableManual = localDataIn.enableManual;

		Serial.print("joyX: ");Serial.println(convertedData.joystickX);
		Serial.print("joyY: ");Serial.println(convertedData.joystickY);
		Serial.print("posX: ");Serial.println(convertedData.posX);
		Serial.print("posY: ");Serial.println(convertedData.posY);
		Serial.print("enableMagnet: ");Serial.println(convertedData.enableMagnet);
		Serial.print("enableManual: ");Serial.println(convertedData.enableManual);
		Serial.print("angle: ");Serial.println(localDataIn.headAngle);


        switch (localDataIn.enableManual){
			case 1:
				localDataOut = manualControl(convertedData);
				break;
			case 0:
				localDataOut = autonomousCountrol(convertedData);
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
	const TickType_t updateFrequency = 1; //Number of ticks between each update

	const unsigned short pwmX = 10;
	const unsigned short pwmY = 11;
	const unsigned short enableX = 8;
	const unsigned short enableY = 9;
	const unsigned short magnetEnable = 2;
	const unsigned short magnetLED = 50; //blue wire
	const unsigned short manualLED = 52; //green wire
  
	pinMode(pwmX,OUTPUT);
	pinMode(pwmY,OUTPUT);
	pinMode(enableX,OUTPUT);
	pinMode(enableY,OUTPUT);
	pinMode(magnetEnable,OUTPUT);
	pinMode(magnetLED, OUTPUT);
	pinMode(manualLED, OUTPUT);

	Serial.println("Output thread started");
    while (true)
    {
        if(xSemaphoreTake(dataOut_semaphore, (TickType_t) 5) == pdTRUE){
			localDataOut = dataOut;
			xSemaphoreGive(dataOut_semaphore);
        }

		bool tempMagnetEnable = localDataOut.magnetEnable;
		String magnetOn = String("M" + String(tempMagnetEnable));

		//vTaskSuspendAll();
		Serial.print("enableX");Serial.println(localDataOut.enableX);		
		Serial.print("enableY");Serial.println(localDataOut.enableY);
		Serial.print("pwmX");Serial.println(localDataOut.pwmX);
		Serial.print("pwmY");Serial.println(localDataOut.pwmY);
		Serial.print("enableMagnet");Serial.print(localDataOut.magnetEnable);
		Serial.println(magnetOn);
		

		analogWrite(pwmX,localDataOut.pwmX);
		analogWrite(pwmY,localDataOut.pwmY);
		digitalWrite(enableX,localDataOut.enableX);
		digitalWrite(enableY,localDataOut.enableY);
		Serial3.println(magnetOn);
		digitalWrite(manualLED, localDataOut.manualEnabled);
		digitalWrite(magnetLED, localDataOut.magnetEnable);
		

		vTaskDelayUntil(&lastWakeTime, updateFrequency);
    }
}
