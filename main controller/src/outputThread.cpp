#include <Arduino.h>



//Inputs
int motorX;
int motorY;
bool enableX;
bool enableY;

//Outputs
const unsigned short pwmX = 41;
const unsigned short pwmY = 42;
const unsigned short enableX = 39;
const unsigned short enableY = 40;

void setup() {
  Serial.begin(9600);
  pinMode(pwmX,OUTPUT);
  pinMode(pwmY,OUTPUT);
  pinMode(enableX,OUTPUT);
  pinMode(enableY,OUTPUT);
}

void loop() {

  /*
    0-26 = død
    229-255 = Død
    Joystick til venstre - Motor den ene retning 26-126
    Joystick til højre - Motor den anden retning 128-229
    Joystick i modten - Dødzone 127-128
  */
}