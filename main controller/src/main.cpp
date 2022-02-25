//Include libraries  
#include <Arduino.h>
#include <manuelFunctions.h>

//Define input pins
#define joystick_x A9
#define joystick_y A8
#define joystick_sw A10
#define magnet_sw 2
#define auto_manuel_sw 3
#define x_pos A0
#define y_pos A1

//Define output pins
#define enable_x 8
#define enable_y 9
#define pwm_x 10
#define pwm_y 11

//Global input variables
float joystickX = 0;
float joystickY = 0;
bool joystickSw = 0;
bool magnetSw = 0;
bool autoManuelSw = 0;
int xPos = 0; 
int yPos = 0;
float angle = 0;

//Global output variables
int pwmX = 127;
int pwmY = 127;


void setup() {

  //Set input pinMode
  pinMode(joystick_x,INPUT);
  pinMode(joystick_y,INPUT);
  pinMode(joystick_sw,INPUT);
  pinMode(magnet_sw,INPUT);
  pinMode(auto_manuel_sw,INPUT);
  pinMode(x_pos,INPUT);
  pinMode(y_pos,INPUT);

  //Set output pinMode
  pinMode(enable_x,OUTPUT);
  pinMode(enable_y,OUTPUT);
  pinMode(pwm_x,OUTPUT);
  pinMode(pwm_y,OUTPUT);

  //Iniliziaze serial
  Serial3.begin(9600);
  Serial.begin(115200);

  Serial.println("Starting...");
}

//Reads all inputs to the system
void input() {
  joystickX = analogRead(joystick_x);
  joystickY = analogRead(joystick_y);
  joystickSw = digitalRead(joystick_sw);
  magnetSw = digitalRead(magnet_sw);
  autoManuelSw = digitalRead(auto_manuel_sw);
  xPos = analogRead(x_pos);
  yPos = analogRead(y_pos);

  Serial.println(joystickX);

  //Reads angle data from head
   //if (Serial3.available() > 0) {
    //String angleData;
    //angleData = Serial3.readString();
    //angle = angleData.toFloat();
   //}
}

//Manuel control
void manuel() {
  //Determines the pwm value from joystick position
  pwmX = joystickOutputFormat(joystickX);
  pwmY = 255 - joystickOutputFormat(joystickY);

  //Sends pwm signals to motor driver x
  if (joystickDeadZone(joystickX) == 1) {
    analogWrite(pwm_x,pwmX);
    digitalWrite(enable_x, HIGH);
  }
  else {
    analogWrite(pwm_x,127);
    digitalWrite(enable_x, LOW);
  }

  //Sends pwm signals to motor driver y
  if (joystickDeadZone(joystickY) == 1) {
    analogWrite(pwm_y,pwmY);
    digitalWrite(enable_y, HIGH);
  }
  else {
    analogWrite(pwm_y,127);
    digitalWrite(enable_y, LOW);
  }

}

void automatic() {

}


void loop() {
  input();

  //Determines manuel or automatic operation
  if(autoManuelSw == 1) {
  manuel();
  }
  else{
    automatic();
  }
}