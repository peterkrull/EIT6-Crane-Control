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

    vTaskSuspendAll();
    if(Serial3.available() > 0){
        delay(1);
        //String tempAngle = Serial3.readStringUntil(*"\n");
        //if(!tempAngle.equals("")) toReturn.headAngle = tempAngle.toFloat();
        String read = Serial3.readString();

        Serial.println(read);

        Serial3.flush();

        //Serial3.readStringUntil(*"\n");
        //float tempAngle = Serial3.parseFloat();
        //Serial.print("Angle ");Serial.println(tempAngle);
    }
    xTaskResumeAll();

    return toReturn;
}