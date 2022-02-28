// Include libraries  
#include <Arduino.h>
#include <manuelFunctions.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include "sigProc.h"

// Definitions for screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define input pins
#define joystick_x A9
#define joystick_y A8
#define joystick_sw A10
#define magnet_sw 2
#define auto_manuel_sw 3
#define x_pos A0
#define y_pos A1
#define magnet_led 50
#define auto_manuel_led 52

// Define output pins
#define enable_x 8
#define enable_y 9
#define pwm_x 10
#define pwm_y 11

// Global input variables
float joystickX = 0;
float joystickY = 0;
bool joystickSw = 0;
bool magnetSw = 0;
bool autoManuelSw = 0;
float xPos = 0; 
float yPos = 0;
float angle = 0;

// Global output variables
int pwmX = 127;
int pwmY = 127;

uint32_t prevTime;
uint16_t delta;
uint32_t screenTimer;

void setup() {

  // Set input pinMode
  pinMode(joystick_x,INPUT);
  pinMode(joystick_y,INPUT);
  pinMode(joystick_sw,INPUT);
  pinMode(magnet_sw,INPUT);
  pinMode(auto_manuel_sw,INPUT);
  pinMode(x_pos,INPUT);
  pinMode(y_pos,INPUT);

  // Set output pinMode
  pinMode(enable_x,OUTPUT);
  pinMode(enable_y,OUTPUT);
  pinMode(pwm_x,OUTPUT);
  pinMode(pwm_y,OUTPUT);
  pinMode(auto_manuel_led,OUTPUT);
  pinMode(magnet_led,OUTPUT);

  // Initialize serial
  Serial3.begin(9600);
  Serial.begin(115200);

  // Initialize screen
  delay(2000);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Wait crane starting.."));
  display.setCursor(0,20);
  display.println(F("EIT6 CE6 630"));
  display.display();
  delay(2000);

  // Printing starting on serial 0
  Serial.println("Starting...");
}

// Reads all inputs to the system
void input() {
  joystickX = analogRead(joystick_x);
  joystickY = analogRead(joystick_y);
  joystickSw = digitalRead(joystick_sw);
  magnetSw = digitalRead(magnet_sw);
  autoManuelSw = digitalRead(auto_manuel_sw);
  xPos = 0.0048*analogRead(x_pos)-0.6765;
  yPos = 0.0015*analogRead(y_pos)-0.0025;

  // Reads angle data from head
  if (Serial3.available() > 0) {
    String angleData;
    angleData = Serial3.readStringUntil(*"\n");
    angle = angleData.toFloat();
  }
}

//Manuel control
void manuel() {
  // Turns on LED when in manuel control
  digitalWrite(auto_manuel_led,HIGH);

  // Determines the pwm value from joystick position
  pwmX = joystickOutputFormat(joystickX);
  pwmY = 255 - joystickOutputFormat(joystickY);

  // Sends pwm signals to motor driver x
  if (joystickDeadZone(joystickX) == 1) {
    analogWrite(pwm_x,pwmX);
    digitalWrite(enable_x, HIGH);
  }
  else {
    analogWrite(pwm_x,127);
    digitalWrite(enable_x, LOW);
  }

  // Sends pwm signals to motor driver y
  if (joystickDeadZone(joystickY) == 1) {
    analogWrite(pwm_y,pwmY);
    digitalWrite(enable_y, HIGH);
  }
  else {
    analogWrite(pwm_y,127);
    digitalWrite(enable_y, LOW);
  }

  // Turns on LED when magnet is active
  if (magnetSw == 1)
  {
    digitalWrite(magnet_led,HIGH);
    Serial3.println("M1");
  }
  else{
    digitalWrite(magnet_led,LOW);
    Serial3.println("M0");
  }
}


// Automatic control
void automatic() {
  // Turn off LED when automatic control is enabled
  digitalWrite(auto_manuel_led, LOW);

}

low_pass oled_freq_lp = low_pass(0.2);

// Display system information on OLED
void screen() {
  if (1e6/(micros()-screenTimer) < 30){
    screenTimer = micros();

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(("X "+String(xPos)));
    display.setCursor(50,0);
    display.println(("Y "+String(yPos)));
    display.setCursor(0,10);
    display.println(("A "+String(angle)));
    display.setCursor(50,10);
    display.println(("Hz "+String(1e6/float(oled_freq_lp.update(delta)))));

    display.display();
  }
}



void loop() {

  // Calculate loop time
  uint32_t xmicros = micros();
  delta = xmicros - prevTime;
  prevTime = xmicros;

  // Reads inputs
  input();

  // Determines manuel or automatic operation
  if(autoManuelSw == 1) {
    manuel();
  } else {
    automatic();
  }

  // Update screen contents
  screen();
}