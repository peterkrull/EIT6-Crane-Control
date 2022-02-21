#include <MainThreadFunc.h>
#include <OutputThreadFunc.h>
#include <InputThreadFunc.h>

struct DataOut manualControl(ConvertedData convertedData){
    DataOut toReturn;
    toReturn.magnetEnable = convertedData.enableMagnet;
    toReturn.enableX = joystickDeadZone(convertedData.joystickX);
    toReturn.enableY = joystickDeadZone(convertedData.joystickY);
    toReturn.pwmX = joystickOutputFormat(convertedData.joystickX);
    toReturn.pwmY = joystickOutputFormat(convertedData.joystickY);
    toReturn.manualEnabled = true;

    return toReturn;
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

float tacoX_Converter(int input){
    short toReturn = 0;
    return toReturn;
}
float tacoY_Converter(int input){
    short toReturn = 0;
    return toReturn;
}


bool joystickDeadZone(float dataJoystick){
    bool toReturn;
    float buffer = 5;
    
    if(511.5+buffer > dataJoystick  && dataJoystick > 511.5-buffer){
        toReturn = 0;
    }
    else{
        toReturn = 1;
    }
    return toReturn;
}

int joystickOutputFormat(float dataJoystick){
    int toReturn = int(0.19844*dataJoystick+26);
    return toReturn;
}



struct DataOut autonomousCountrol(ConvertedData convertedData){
    DataOut toReturn;
    toReturn.enableX = 0;
    toReturn.enableY = 0;
    toReturn.pwmX = 0;
    toReturn.pwmY = 0;
    toReturn.magnetEnable = convertedData.enableMagnet;
    toReturn.manualEnabled = false;

    return toReturn;
}
