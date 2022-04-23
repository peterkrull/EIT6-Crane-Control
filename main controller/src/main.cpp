// Include libraries  
#include <Arduino.h>
#include <functions.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include "sigProc.h"
#include "path.h"
#include "math.h"
#include "pinDefinitions.h"
#include "dataStructures.h"
#include "displayHandler.h"

// Configuration
#define SAMPLEHZ 100        // Control loop sample frequency
#define OLEDHZ   30         // Oled display refresh rate
// #define USEPATHALGO      // Uncomment if path algorithm is to be used

// Definitions for screen
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C

// x-controller variables
#define xOuterZ 2.41
#define xOuterP 0.35
#define xOuterG 1.50

#define xInnerP 0.9
#define xInnerD 9.0
#define xInnerI 0.0

// y-controller variables
#define yP 150.0
#define yI 0.000
#define yD 0.750
#define yLP 0.05

// Controllers on the x-axis
lead_lag xOuterController = lead_lag(xOuterZ,xOuterP,xOuterG);
PID xInnerController = PID(xInnerP, xInnerI, xInnerD, 0, false);

// PID controller for y-axis
PID yController = PID(yP,yI,yD,yLP);

// Loop sample period
uint32_t Ts = 1e6/SAMPLEHZ;

// Data struct definitions
xy_float  ref;
xy_pwm    pwm;
inputs    in;

// Time variables
uint32_t sampleTimer  = 0;
uint32_t screenTimer  = 0;
uint32_t loopTime     = 0;

#ifdef USEPATHALGO
QauyToShip testQuayToShip = QauyToShip();
ShipToQauy testShipToQuay = ShipToQauy();
#endif

// Display object instantiation
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Instantiate filters and forward Eulers
low_pass oledLowpass           = low_pass(0.2);             // Lowpass filter tau = 200 ms.
low_pass xPosLowpasss           = low_pass(0.03);           // Lowpass filter tau = 30 ms.
low_pass yPosLowpasss           = low_pass(0.03);           // Lowpass filter tau = 30 ms.
low_pass angleLowpass           = low_pass(0.03);           // Lowpass filter tau = 30 ms.
forwardEuler xTrolleyVelCal     = forwardEuler();           // For calculating trolley speed in the y-axis
forwardEuler yTrolleyVelCal     = forwardEuler();           // For calculating trolley speed in the x-axis
forwardEuler xContainerVelCal   = forwardEuler();           // For calculating container speed in the x-axis
forwardEuler yContainerVelCal   = forwardEuler();           // For calculating container speed in the y-axis
NotchFilter angleNotchFilter    = NotchFilter(2.35,5,Ts);   // Notch filter for removing 2.35 Hz component

// Run on startup
void setup() {

    // Set safe default reference values
    #ifndef USEPATHALGO
    ref.x = 2;  ref.y = 1;
    #endif

    // Set input pinMode
    pinMode(pin_joystick_x,   INPUT);
    pinMode(pin_joystick_y,   INPUT);
    pinMode(pin_joystick_sw,  INPUT);
    pinMode(pin_magnet_sw,    INPUT);
    pinMode(pin_ctrlmode_sw,  INPUT);
    pinMode(pin_pos_x,        INPUT);
    pinMode(pin_pos_y,        INPUT);

    // Set output pinMode
    pinMode(pin_enable_x,     OUTPUT);
    pinMode(pin_enable_y,     OUTPUT);
    pinMode(pin_pwm_x,        OUTPUT);
    pinMode(pin_pwm_y,        OUTPUT);
    pinMode(pin_ctrlmode_led, OUTPUT);
    pinMode(pin_magnet_led,   OUTPUT);

    // Initialize serial
    Serial3.begin(9600);  // Communication with head
    Serial.begin(115200); // Communication with PC

    // Initialize Oled display
    initializeDisplay(&display);

    // Print controller values
    Serial.println("//xOuterZ: " + String(xOuterZ) + ", xOuterP: " + String(xOuterP) + ", xOuterG: " + String(xOuterG));
    Serial.println("//xInnerP: " + String(xInnerP) + ", xInnerI: " + String(xInnerI) + ", xInnerD: " + String(xInnerD));
    Serial.println("//yP: " + String(yP) + ", yI: " + String(yI) + ", yD: " + String(yD));
}

// Function that reads the inputs to the system and makes convertions
void readInput() {

    // Fetches reference point from serial readout
    #ifndef USEPATHALGO
    getSerialReference(&Serial,&ref);
    #endif

    in.joystick.x    = analogRead(pin_joystick_x);          // Reads joystick x-direction
    in.joystick.y    = 511.5-analogRead(pin_joystick_y);    // Reads joystick y-direction
    in.joystickSw    = digitalRead(pin_joystick_sw);        // Reads joystick switch
    in.magnetSw      = digitalRead(pin_magnet_sw);          // Reads magnet switch on the controller
    in.ctrlmodeSw    = digitalRead(pin_ctrlmode_sw);        // Reads control mode on the controller
    in.posTrolley.x  = 0.0048*analogRead(pin_pos_x)-0.6765; // Read x-potentiometer and convert to meters
    in.posTrolley.y  = 0.0015*analogRead(pin_pos_y)-0.0725; // Read y-potentiometer and convert to meters
    in.xDriverAO1    = analogRead(pin_x_driver_AO1);        // Read analog output from driver
    in.xDriverAO2    = analogRead(pin_x_driver_AO2);        // Read analog output from driver
    in.yDriverAO1    = analogRead(pin_y_driver_AO1);        // Read analog output from driver
    in.yDriverAO2    = analogRead(pin_y_driver_AO2);        // Read analog output from driver

    //Anlge sensor input
    getAngleSensor(&Serial3,&in.angle);

    // Filter angle input : in -> [ lowpass ] -> [ notch ] -> out
    in.angle = angleNotchFilter.update(angleLowpass.update(in.angle));

    // Filter trolley position inputs
    in.posTrolley.x = xPosLowpasss.update(in.posTrolley.x);
    in.posTrolley.y = yPosLowpasss.update(in.posTrolley.y);

    // Calculate container position
    in.posContainer.x = in.posTrolley.x+(sin((-in.angle*PI)/180))*in.posTrolley.y;
    in.posContainer.y = in.posTrolley.y+(cos((-in.angle*PI)/180))*in.posTrolley.y;

    // Calculate speed x-axis and y-axis
    in.velTrolley.x = xTrolleyVelCal.update(in.posContainer.x);
    in.velTrolley.y = yTrolleyVelCal.update(in.posContainer.y);

    // Calculate contrainer speed
    in.velContainer.x = xContainerVelCal.update(in.posContainer.x);
    in.velContainer.y = yContainerVelCal.update(in.posContainer.y);

    // Calculates absolute velocity of container
    in.velContainerAbs = sqrt(pow(in.velContainer.x,2) + pow(in.velContainer.y,2));
}

//Manual control
void manualControl() {
    // Turns on LED when in manual control
    digitalWrite(pin_ctrlmode_led,HIGH);

    // Calculates actuations based on joystick and trolley position
    pwm.x = endstop(in.joystick.x, 0.0, 4.00, in.posTrolley.x);
    pwm.y = endstop(in.joystick.y, 0.0, 1.62, in.posTrolley.y);
    
    // Sends pwm signals to motor driver x
    // if joystick is not in middle position
    if (joystickDeadZone(in.joystick.x) == 1) {
        analogWrite(pin_pwm_x,pwm.x);
        digitalWrite(pin_enable_x, HIGH);
    } else {
        analogWrite(pin_pwm_x,127);
        digitalWrite(pin_enable_x, LOW);
    }

    // Sends pwm signals to motor driver y
    // if joystick is not in middle position
    if (joystickDeadZone(in.joystick.y) == 1) {
        analogWrite(pin_pwm_y,pwm.y);
        digitalWrite(pin_enable_y, HIGH);
    } else {
        analogWrite(pin_pwm_y,127);
        digitalWrite(pin_enable_y, LOW);
    }

    // Turns on LED and magnet when magnet switch is active
    if (in.magnetSw == 1) {
        turnOnElectromagnet(true, pin_magnet_led);
    } else {
        turnOnElectromagnet(false, pin_magnet_led);
    }
}

// Automatic control
void automaticControl() {
    // Turn off LED when automatic control is enabled
    digitalWrite(pin_ctrlmode_led, LOW);

    //Define enable value for x-axis motor
    bool enableXmotor = true;

    #ifdef USEPATHALGO
    testQuayToShip.update( in.posTrolley.x, in.posTrolley.y, in.posContainer.x, in.velContainerAbs, &ref.x, &ref.y, pin_magnet_led);
    #endif

    // X-controller
    double xInnerConOut = xInnerController.update(-in.angle*PI/180);
    double xOuterConOut = xOuterController.update(ref.x-in.posTrolley.x, 0.01)*xOuterG;
    double xConOut      = xOuterConOut-xInnerConOut;

    // Y-controller
    double yConOut = yController.update(ref.y-in.posTrolley.y);

    // Make current to pwm conversion. This also removes friction in the system
    uint8_t pwmx = currentToPwmX(xConOut, in.velTrolley.x, &enableXmotor);
    uint8_t pwmy = currentToPwmY(yConOut, in.velTrolley.y, in.magnetSw);
    
    // Definere software endstops
    pwm.x = endstop(pwmx, 0.2, 3.80, in.posTrolley.x);
    pwm.y = endstop(pwmy, 0.0, 1.22, in.posTrolley.y);

    // Outputs the PWM signal
    digitalWrite(pin_enable_x, enableXmotor);
    analogWrite(pin_pwm_x,pwm.x);

    digitalWrite(pin_enable_y,HIGH);
    analogWrite(pin_pwm_y,pwm.y);
}

// Main loop
void loop() {

    // Calculate loop frequency
    uint32_t xmicros = micros();
    uint16_t loopFreq = 1e6/oledLowpass.update(xmicros - loopTime);
    loopTime = xmicros;

    // For manual control
    if(digitalRead(pin_ctrlmode_sw) == 1) {
        displayInfo(&display,in,loopFreq,&screenTimer);
        readInput();
        manualControl(); 
    } 

    // For automatic control
    else if(micros() > Ts + sampleTimer){
        sampleTimer += Ts;
        readInput();
        automaticControl();
        getAngleSensor(&Serial3,&in.angle); // Reads angle again to avoid serial buffer overflow
    }
}