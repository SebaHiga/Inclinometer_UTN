#pragma once

#include <main.hpp>
#include <MPU6050.hpp>

extern MPU6050 mpu;


void TaskAccel(void *pvParameters);