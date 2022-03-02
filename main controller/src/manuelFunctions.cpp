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

int8_t currentToPwm(float current) {

    if (current > 10) current = 10;
    if (current < -10) current = -10;

    float pwm = 10.2*current+127.5;

    if (current < 0) {
        pwm = pwm - 23.5;
    } else if (current > 0) {
         pwm = pwm + 23.5;
    }

    int8_t returnPwm = (int8_t)pwm;

    if ((int8_t)pwm > 255*0.9) returnPwm = (int8_t)255*0.9;
    else if ((int8_t)pwm < 255*0.1) returnPwm = (int8_t)255*0.1;
    
    return returnPwm ;    
}