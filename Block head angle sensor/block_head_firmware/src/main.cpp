#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "I2Cdev.h"
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps_V6_12.h"

#define LED_BUILTIN 12

void vMPU(void *pvParameters) {

  MPU6050 mpu;

  bool dmpReady = false;  // set true if DMP init was successful
  uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
  uint8_t fifoBuffer[64]; // FIFO storage buffer

  // orientation/motion vars
  Quaternion q;           // [w, x, y, z]         quaternion container
  VectorFloat gravity;    // [x, y, z]            gravity vector
  float ypr[3];

  // Initialize MPU
  Wire.begin();
  delay(20);
  mpu.initialize();

  if (mpu.dmpInitialize() == 0){
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.setDMPEnabled(true);
    mpu.setDLPFMode(MPU6050_DLPF_BW_98);
    packetSize = mpu.dmpGetFIFOPacketSize();
  }

  const TickType_t xFrequency = 100;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  // Thread loop
  while (true)
  {
    vTaskDelayUntil(&xLastWakeTime, int(1000 / xFrequency));
    
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  }
}

void vSerialSND(void *pvParameters) {

}

void vSerialRCV(void *pvParameters) {
  
}

void setup() {

  float angle;
  
  xTaskCreate(vMPU, "vMPU", 8000, &angle, 1, NULL);
  xTaskCreate(vSerialSND, "vSerialSND", 8000, &angle, 1, NULL);
  xTaskCreate(vSerialRCV, "vSerialRCV", 8000, &angle, 1, NULL);
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}