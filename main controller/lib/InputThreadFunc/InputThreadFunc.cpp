#include <InputThreadFunc.h>

DataIn readInput(void){
    InputPins pins;

    DataIn toReturn;

    toReturn.toggleMagnet = digitalRead(pins.toggleMagnet);
    toReturn.toggleManual = digitalRead(pins.toggleManual);
    toReturn.joystickX = analogRead(pins.joystickX);
    toReturn.joystickY = analogRead(pins.joystickY);
    //toReturn.tacoX = analogRead(pins.tacoX);
    //toReturn.tacoY = analogRead(pins.tacoY);
    toReturn.posX = analogRead(pins.posX);
    toReturn.posY = analogRead(pins.posY);
    toReturn.measurementTime = millis();
    if(Serial3.available() > 0){
        String tempAngle = Serial3.readStringUntil(*"\n");
        if(!tempAngle.equals("")) toReturn.headAngle = tempAngle.toFloat();
    }
    

    return toReturn;
}