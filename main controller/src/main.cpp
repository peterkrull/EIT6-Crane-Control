// Include libraries  
#include <Arduino.h>
#include <Functions.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include "sigProc.h"
#include "path.h"
#include "math.h"

// Definitions for screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define input pins
#define joystick_x A9 // Joystick x-axis
#define joystick_y A8 // Joystick y-axis
#define joystick_sw A10 // Joystick switch
#define magnet_sw 2 // Magnet switch
#define auto_manuel_sw 3 // Switch from manuel to automatic control
#define x_pos A0 // Input from x-axis potentiometer
#define y_pos A1 // Input from y-axis potentiometer
#define x_driver_AO1 A5 // Input from x motor driver AO1
#define x_driver_AO2 A4 // Input from x motor driver AO2
#define y_driver_AO1 A3 // Input from y motor driver AO1
#define y_driver_AO2 A2 // Input from y motor driver AO2

// Define output pins
#define enable_x 8 // Enable driver x
#define enable_y 9 // Enable driver y
#define pwm_x 10 // PWM pin driver x
#define pwm_y 11 // PWM pin driver x
#define magnet_led 50 // LED showing status of magnet
#define auto_manuel_led 52 // LED showing status of auto or manuel control

// Global input variables
float joystickX = 0; // Joystick x-axis
float joystickY = 0; // Joystick y-axis
bool joystickSw = 0; // Joystick switch
bool magnetSw = 0; // State of magnet switch
bool autoManuelSw = 0; // State of manuel or automatic control
float xPos = 0; // Position of x-axis
float yPos = 0; // Position of y-axis
float angle = 0; // Angle of head
float angleFiltered = 0; // Filtered angle of head
float prevAngle = 0; // Previous angle inside +- 35 degrees  
int yDriverAO1 = 0; // Value of y motor driver A01
int yDriverAO2 = 0; // Value of y motor driver A02
int xDriverAO1 = 0; // Value of x motor driver A01
int xDriverAO2 = 0; // Value of x motor driver A02

// Global output variables
int pwmX = 127; // PWM value x motor driver
int pwmY = 127; // PWM value y motor driver

// Time variables
uint32_t prevTime1 = 0;
uint32_t prevTime = 0;
uint16_t delta =0;
uint32_t screenTimer;
int sampleTime = 10000; // 10 ms.    // Path algorithme speed test will fail if lower than 10 ms.

// Container pos
float xContainer = 0; // Position of container x-axis
float yContainer = 0; // Position of container y-axis

// Speeds
float xContainerSpeed = 0; // Speed of container x-axis
float yContainerSpeed = 0; // Speed of container y-axis
float ContainerSpeed = 0; // Speed of container
float xSpeed = 0; // Speed of x-axis
float ySpeed = 0; // Speed of y-axis


//Xcontroller variables
float XleadZeroCoef = 2.41;
float XleadPoleCoef = 0.35;
float XP = .10;
float XD = 1;
float XI = 0;
float thetaGain = 9;
float xGain = 1.5;


// Run on startup
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
  Serial3.begin(9600); // Communication with head
  Serial.begin(115200); // Communication with PC

  // Initialize screen
  delay(2000); // This delay ensures that the screen is started before sending data to it
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

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Crane Ready!"));
  display.display();

  Serial.println("//XleadZeroCoefficient: " + String(XleadZeroCoef) + ", XleadPoleCoefficient: " + String(XleadPoleCoef) + ", XleadGain" + String(xGain));
  Serial.println("//PX: " + String(XP)+ ", IX: " + String(XI) + ", DX: " + String(XD) +", angleGain" + String(thetaGain));
}

// Read data for the angle sensor. Must run often.
void inputAngleSensor(){
    if (Serial3.available() > 0) {
      String angleData;
      angleData = Serial3.readStringUntil(*"\n");
      angle = angleData.toFloat();

      if(angle > 35 || angle < -35){
        angle = prevAngle;
      }
      prevAngle = angle;
  }
}

// Reads all inputs to the system
low_pass xPosLowpasss = low_pass(0.03); // Lowpass filter tau = 30  ms.
low_pass yPosLowpasss = low_pass(0.03); // Lowpass filter tau = 30  ms.
low_pass xContainerLowpasss = low_pass(0.03); // Lowpass filter tau = 30  ms.
low_pass yContainerLowpasss = low_pass(0.03); // Lowpass filter tau = 30  ms.
low_pass angleLowpass = low_pass(1/30); // Lowpass angle to remove obscene values
forwarEuler xForwarEuler = forwarEuler(); // Make object xForwarEuler used for calculating speed in the y-axis
forwarEuler yForwarEuler = forwarEuler(); // Make object yForwarEuler used for calculating speed in the x-axis
forwarEuler xContainerForwarEuler = forwarEuler(); // Make object xContainerForwarEuler used for calculating speed in the container x-axis
forwarEuler yContainerForwarEuler = forwarEuler(); // Make object yContainerForwarEuler used for calculating speed in the container y-axis

// Function that reads the inputs to the system and makes convertions
void input() {
  joystickX = analogRead(joystick_x); // Reads joystick x-direction
  joystickY = analogRead(joystick_y); // Reads joystick y-direction
  joystickSw = digitalRead(joystick_sw); // Reads joystick switch
  magnetSw = digitalRead(magnet_sw); // Reads magnet switch on the controller
  autoManuelSw = digitalRead(auto_manuel_sw); // Reads manuel or automatic switch on the controller
  xPos = 0.0048*analogRead(x_pos)-0.6765; // Read x-potentiometer and convert to meters
  yPos = (0.0015*analogRead(y_pos)-0.0025)-0.07; // Read y-potentiometer and convert to meters
  xDriverAO1 = analogRead(x_driver_AO1); // Read analouge output from driver
  xDriverAO2 = analogRead(x_driver_AO2); // Read analouge output from driver
  yDriverAO1 = analogRead(y_driver_AO1); // Read analouge output from driver
  yDriverAO2 = analogRead(y_driver_AO2); // Read analouge output from driver

  //Anlge sensor input
  inputAngleSensor(); // Reads the angle of the head
  angle = angleLowpass.update(angle); // lowpass angle of the head

  // Calculate container pos
  xContainer = xPos+(sin((-angle*PI)/180))*yPos; // Calculate x-container position
  yContainer = yPos+(cos((-angle*PI)/180))*yPos; // Calculate y-container position

  // Calculate speed x-axis and y-axis
  xSpeed = xForwarEuler.update(xPosLowpasss.update(xPos)); // Calculate speed in x-axis
  ySpeed = yForwarEuler.update(yPosLowpasss.update(yPos)); // Calculate speed in y-axis

  // Calculate contrainer speed
  xContainerSpeed = xContainerForwarEuler.update(xContainerLowpasss.update(xContainer)); // Calculate speed of container x-axis
  yContainerSpeed = yContainerForwarEuler.update(yContainerLowpasss.update(xContainer)); // Calculate speed of container y-axis
  ContainerSpeed = sqrt(xContainerSpeed*xContainerSpeed + yContainerSpeed*yContainerSpeed); // Calculate speed of container
  
}

//Manuel control
void manuel() {
  // Turns on LED when in manuel control
  digitalWrite(auto_manuel_led,HIGH);

  // Determines the pwm value from joystick position with software endstop (endstop(pwm, min, max, pos))
  pwmX = endstop(joystickOutputFormat(joystickX), 0.0, 4, xPos);
  pwmY = endstop(255 - joystickOutputFormat(joystickY), 0.0, 1.62, yPos);
  
  // Sends pwm signals to motor driver x
  if (joystickDeadZone(joystickX) == 1) {   //If joystick is not in the middel
    analogWrite(pwm_x,pwmX);
    digitalWrite(enable_x, HIGH);
  }
  else {
    analogWrite(pwm_x,127);                 //if joystick is in the middel
    digitalWrite(enable_x, LOW);
  }

  // Sends pwm signals to motor driver y
  if (joystickDeadZone(joystickY) == 1) {   //If joystick is not in the middel
    analogWrite(pwm_y,pwmY);
    digitalWrite(enable_y, HIGH);
  }
  else {
    analogWrite(pwm_y,127);                 //if joystick is in the middel
    digitalWrite(enable_y, LOW);
  }

  // Turns on LED and magnet when magnet switch is active
  if (magnetSw == 1)
  {
    turnOnElectromagnet(true, magnet_led);
  }
  else{
    turnOnElectromagnet(false, magnet_led);
  }
}

// Controllers on the x-axis
lead_lag xController = lead_lag(1/XleadZeroCoef, 1/XleadPoleCoef, XleadZeroCoef/XleadPoleCoef);
PID angleController = PID(XP, XI, XD, 0, false);

// Notch filter that removes unwanted angle frequencies (old)
// float b[3] = {1.0, -1.9553, 0.9738};
// float a[3] = {1.0, -1.7276, 0.7462};

/* Pre-warped Tustin-filter (Wiki)
Dz_spike =
 
  0.8649 z^2 - 1.711 z + 0.8649
  -----------------------------
     z^2 - 1.711 z + 0.7298
*/
float b[3] = {0.8649, -1.711, 0.8649};
float a[3] = {1.0000, -1.711, 0.7298};

IIR angleNotchFilter = IIR(a, b);

// PID controller for y-axis
PID yPid = PID(150,0,75,0.05);

//QauyToShip testQuayToShip = QauyToShip();

low_pass oled_freq_lp = low_pass(0.2);

// Refference signals (Can be used if refference system is inactive)
float xRef = 2;
float yRef = 1;

// Automatic control
void automatic() {
  // Turn off LED when automatic control is enabled
  digitalWrite(auto_manuel_led, LOW);

  //Define enable value for x-axis motor
  bool enableXmotor = true;

  //testQuayToShip.update( xPos, yPos, xContainer, ContainerSpeed, &xRef, &yRef, magnet_led);

  
  // Calculate filtered angle
  angleFiltered = angleNotchFilter.update(angle);

  // X-controller
  double angleConOutput = thetaGain*angleController.update(-angleFiltered*PI/180);
  double xConOutput = xGain*xController.update(xRef-xPos, 0.01);
  double XconOut = xConOutput-angleConOutput;


  // Y-controller
  double YconOut = yPid.update(yRef-yPos);

  // Make current to pwm conversion. This also removes friction in the system
  uint8_t pwmx = currentToPwmX(XconOut, xSpeed, &enableXmotor);
  uint8_t pwmy = currentToPwmY(YconOut, magnetSw, ySpeed);
  

  // Definere software endstops
  pwmX = endstop(pwmx,0.2,3.8,xPos);
  pwmY = endstop(pwmy,0,1.22,yPos);

  // Outputs the PWM signal
  digitalWrite(enable_x, enableXmotor);
  analogWrite(pwm_x,pwmX);

  digitalWrite(enable_y,HIGH);
  analogWrite(pwm_y,pwmY);
}


// Display system information on OLED
void screen() {
  if (1e6/(micros()-screenTimer) < 30){ // Update OLED screen with xx frequency
    screenTimer = micros();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(("X "+String(xPos)));
    display.setCursor(70,0);
    display.println(("Y "+String(yPos)));
    display.setCursor(0,10);
    display.println(("A "+String(angle)));
    display.setCursor(70,10);
    display.println(("Hz "+String(1e6/float(oled_freq_lp.update(delta)))));
    display.setCursor(0,20);
    display.println(("Xc "+String(xContainer)));
    display.setCursor(70,20);
    display.println(("Yc "+String(yContainer)));
    display.display();
  }
}

// Main loop
void loop() {
  // Calculate loop time
  uint32_t xmicros = micros();
  delta = xmicros - prevTime;
  prevTime = xmicros;

  // Determines manuel or automatic operation
  if(digitalRead(auto_manuel_sw) == 1) {
    screen(); // Update screen
    input();  // Read inputs
    manuel(); // Manuel control
  } 

  // if auctomatic and sample time
  else if(micros() > sampleTime + prevTime1){
    prevTime1 = micros();
    input(); // Read inputs
    automatic(); // Automatic control
    inputAngleSensor(); // Reads angle sensor in order to avoid overflow value not used (Sensor is read approx 200 Hz because of this)
  }
}