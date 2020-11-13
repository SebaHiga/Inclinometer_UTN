#pragma once
#include <Arduino.h>
#include <MPU6050.hpp>

class Inclinometer {
public:
    void begin();

    static void run(void *pvParameters);

private:
    static MPU6050 mpu;
};