#include <InputThreadFunc.h>

DataIn readInput(void){
    InputPins pins;

    DataIn toReturn;

    toReturn.enableMagnet = digitalRead(pins.enableMagnet);
    toReturn.enableManual = digitalRead(pins.enableManual);
    toReturn.joystickX = analogRead(pins.joystickX);
    toReturn.joystickY = 1023-analogRead(pins.joystickY);
    //toReturn.tacoX = analogRead(pins.tacoX);
    //toReturn.tacoY = analogRead(pins.tacoY);
    toReturn.posX = analogRead(pins.posX);
    toReturn.posY = analogRead(pins.posY);
    toReturn.measurementTime = millis();

    Serial.print("\nBytes in serial3 : ");
    Serial.println(Serial3.available());
    Serial3.flush();
    Serial.print("Bytes in serial3 : ");
    Serial.println(Serial3.available());
    //if (Serial3.available()>0){}

    //vTaskSuspendAll();


    
    int serialBytes = Serial3.available();

    char rcv [8];
    if(serialBytes > 7){
        Serial3.readBytes(rcv, 8);
        //toReturn.headAngle = rcv.toFloat();
        
    }else toReturn.headAngle = 0;
    toReturn.headAngle = 0;
    
    //xTaskResumeAll();

    return toReturn;
}