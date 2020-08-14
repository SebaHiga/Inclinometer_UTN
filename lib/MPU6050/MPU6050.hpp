#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <vector.hpp>

class MPU6050{
private:
    static const int MPU_addr;
    static const int16_t LSB_g;
    static const int read_delay;
    
    // define vectors
    static vect_t<int16_t> accel;
    static vect_t<int16_t> gyro;

    static bool connected;

public:
    void begin(){
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write(0); // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
        connected = true;
    }

    static void task_read(void *pvParameters);

    static void read();

    static String getFormatted();

    static void printFormatted(void);

    ~MPU6050(){Wire.endTransmission(true);};
};
