#include <Arduino_FreeRTOS.h>
#include <semphr.h>

//Semaphore handling who reads the input data vector
SemaphoreHandle_t dataIn_semaphore;

//Task that reads the inputs and saves them in data_vector
void TaskReadInput(void *pvParameters);

struct DataIn{
	float posX = 0;
	float posY = 0;
	float tacoX = 0;
	float tacoY = 0;
	int joystickX = 0;
	int joystickY = 0;
	bool toggleMagnet = 0;
	bool toggleManual = 0;
	unsigned long measurementTime = 0;
};

DataIn dataIn;


void setup()
{
	Serial.begin(9600);
	Serial3.begin(9600);
	dataIn_semaphore = xSemaphoreCreateMutex();
	if(dataIn_semaphore != NULL) xSemaphoreGive(dataIn_semaphore);

	xTaskCreate(TaskReadInput, "readInput",128, NULL, 1, NULL);

}

void loop()
{
	
}

void TaskReadInput(void *pvParameters __attribute__((unused))){
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

//converts voltage to position in mm
short posY_Converter(int input){
	float toReturn = float(input*5/1023)*0.3966-0.0179;

	return short(toReturn*1000);
}

//converts voltage to position in mm
short posX_Converter(int input){
	
	float toReturn = float(input*5/1023)*1.2844-0.7496;

	return short(toReturn*1000);
}

float joystick_Converter(int input){
	short neutralBuffer = 50;
	float toReturn;

	if(1023/2-neutralBuffer < input && input < 1023/2+neutralBuffer) toReturn = 0;
	else{
		toReturn = 100-input*100/461;
	}

	return toReturn;
}

