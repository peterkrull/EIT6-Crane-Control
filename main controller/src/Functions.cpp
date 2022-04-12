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

uint8_t currentToPwm(double current, bool magnetSw, float xSpeed, float ySpeed, bool axis) {

    // Make more linear for y-axis (axis = 0)
    if(axis == 0){
        // Adjust for gravity
        if (magnetSw == 1){
            current = current - 1.35; // Current gravity with container
        } else{
            current = current - 0.33; // Current gravity without container
        }
        
        // Adjust for friction
        if (abs(current) < 0){ //This number can be set to something larger than 0 if no movement is wanted for small currents
            current = 0;
        } else if (ySpeed < 0) {
            current = current - 3.17; // Columb friction current
        } else if (ySpeed > 0) {
            current = current + 3.17; // Columb friction current
        }

        // Set max speed
        if(abs(ySpeed)>0.5){
           current = 0; 
        }

        // Equalize currents around gravity
        if(current > 10-1.45 && magnetSw ==1){
            current = 10-1.45;
        }
        if(current > 10-0.33 && magnetSw ==0){
            current = 10-0.33;
        }
        if(current < -10){
            current = -10;
        }
    }

    // Make more linear for x-axis (axis = 1)
    if(axis == 1){
        // Adjust for friction
        if (abs(current) < 0){ //This number can be set to something larger than 0 if no movement is wanted for small currents
            current = 0;
        } else if (xSpeed < 0) {
            current = current - 2.21; // Columb friction current
        } else if (xSpeed > 0) {
            current = current + 2.21; // Columb friction current
        }
    }

    //Check for correct current value
    if(current > 10){
        current = 10;
    }
    if(current < -10){
        current = -10;
    }
    
    // Linear current -> pwm conversion
    float pwm = 10.2*current+127.5;
    return (uint8_t)pwm;
}

void turnOnElectromagnet(bool status, int LEDPin){
    if (status == true) {
    digitalWrite(LEDPin,HIGH);
    Serial3.println("M1");
  }

  if(status==false){
    digitalWrite(LEDPin,LOW);
    Serial3.println("M0");
  }
}