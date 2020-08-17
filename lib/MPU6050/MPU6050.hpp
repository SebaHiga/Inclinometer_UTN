#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <vector.hpp>
#include <filter.hpp>

class MPU6050{
private:
    static const int MPU_addr;
    static const int16_t LSB_g;
    static const int read_delay;
    
    // define vectors
    static vect_t<int16_t> accel;
    static vect_t<int16_t> gyro;

    static Filter<int16_t, 3> filter;

    static bool connected;

public:
    void begin(){
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write(0); // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
        connected = true;

        float b[] = {0.00069935, 0.00209805, 0.00209805, 0.00069935};
        float a[] = {-2.62355181,  2.31468258, -0.6855359};
        Array<float, 4> array_b(b);
        Array<float, 3> array_a(a);
        filter.setCoefficients(array_b, array_a);
    }

    static void task_read(void *pvParameters);

    static void read();

    static String getFormatted();

    static void printFormatted(void);

    ~MPU6050(){Wire.endTransmission(true);};
};
