#include <InputThreadFunc.h>

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