#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.hpp>

MPU6050 accelGyro;

void setup() {
	Serial.begin(115200);
	accelGyro.begin();
}


void loop() {
	accelGyro.read();
	Serial.println(accelGyro.getFormated());
	delay(100);
}