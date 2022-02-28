//Include libraries  
#include <Arduino.h>
#include <manuelFunctions.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Define input pins
#define joystick_x A9
#define joystick_y A8
#define joystick_sw A10
#define magnet_sw 2
#define auto_manuel_sw 3
#define x_pos A0
#define y_pos A1
#define magnet_led 50
#define auto_manuel_led 52

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
  pinMode(auto_manuel_led,OUTPUT);
  pinMode(magnet_led,OUTPUT);

  //Iniliziaze serial
  Serial3.begin(9600);
  Serial.begin(115200);

  //Iniliziaze screen
  delay(2000);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Wait crane starting.."));
  display.setCursor(0,20);             // Start at top-left corner
  display.println(F("EIT6 CE6 630"));
  display.display();
  delay(2000); // Pause for 2 seconds

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

  // Reads angle data from head
  if (Serial3.available() > 0) {
    Serial.println("Serial3 is available : "+String(Serial3.available()));
    String angleData;
    angleData = Serial3.readStringUntil(*"\n");
    Serial.println("String has been read : "+angleData);
    angle = angleData.toFloat();
    Serial.println("String has been converted : "+String(angle));
  }
}

//Manuel control
void manuel() {
  //Turns on LED when in manuel control
  digitalWrite(auto_manuel_led,HIGH);

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

  //Turns on LED when magnet is active
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


//Automatic control
void automatic() {
  //Turn off LED when automatic control is enabled
  digitalWrite(auto_manuel_led, LOW);

}

void screen() {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println((String(joystickX)));

  display.display();
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

  screen();
}