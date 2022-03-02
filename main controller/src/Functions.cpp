#include <Arduino.h>

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

// Software endstops (works on the pwm value)
int endstop(int pwm, float min, float max, float pos){
    int pwmEndstop = 127;
    bool dir = 0;
    pwmEndstop = pwm;

    // Check direction (used so it can move in the other direction)
    if (pwm < 127) {
        dir = 0;
    }
    else {
        dir = 1;
    }
    
    // Chek if endstop is hit
    if (pos > max && dir == 1) {
    pwmEndstop = 127;
    }
    if (pos < min && dir == 0) {
    pwmEndstop = 127;
    }

    return pwmEndstop;
}

uint8_t currentToPwm(float current) {

    //Serial.print("Curr in : "+String(current));

    if (current > 10) current = 10;
    if (current < -10) current = -10;

    //Serial.print(" Curr lim : "+String(current));

    float pwm = 10.2*current+127.5;

    //Serial.print(" PWM : "+String(pwm));

    if (current < 0) {
        pwm = pwm - 23.5;
    } else if (current > 0) {
         pwm = pwm + 23.5;
    }

    //Serial.print(" PWM lin : "+String(pwm));

    uint8_t returnPwm = (uint8_t)pwm;

    //Serial.print(" ret PWM : "+String(returnPwm));

    if ((uint8_t)pwm > 255*0.9) returnPwm = (uint8_t)255*0.9;
    else if ((uint8_t)pwm < 255*0.1) returnPwm = (uint8_t)255*0.1;
    
    //Serial.println(" ret PWM fin : "+String(returnPwm));
    
    return returnPwm ;    
}