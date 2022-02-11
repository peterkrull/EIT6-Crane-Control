#include <MainThreadFunc.h>
#include <OutputThreadFunc.h>
#include <InputThreadFunc.h>

struct DataOut manualControl(struct ConvertedData convertedData){
    struct DataOut toReturn;

    toReturn.magnetEnable = convertedData.toggleMagnet;
    

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

bool joystickDeadZone(float dataJoystick){
    bool toReturn;
    if(-5 < dataJoystick < 5){
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
