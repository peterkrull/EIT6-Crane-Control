#include <MainThreadFunc.h>
#include <OutputThreadFunc.h>
#include <InputThreadFunc.h>

void manualControl(ConvertedData convertedData){

    toReturn.magnetEnable = convertedData.toggleMagnet;
    toReturn.enableX = joystickDeadZone(convertedData.joystickX);
    toReturn.enableY = joystickDeadZone(convertedData.joystickY);
    toReturn.pwmX = joystickOutputFormat(convertedData.joystickX);
    toReturn.pwmY = joystickOutputFormat(convertedData.joystickY);


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

bool joystickDeadZone(int dataJoystick){
    bool toReturn;
    float buffer = 1;
    if(511.5+buffer < dataJoystick  && dataJoystick > 511.5-buffer){
        toReturn = 1;
    }
    else{
        toReturn = 0;
    }
    return toReturn;
}

int joystickOutputFormat(float dataJoystick){
    int toReturn = int(0.19844*dataJoystick+26);
    return toReturn;
}
