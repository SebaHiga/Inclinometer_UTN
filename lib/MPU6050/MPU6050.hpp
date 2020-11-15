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

    static Filter<float, 2> filter_x;
    static Filter<float, 2> filter_y;
    static Filter<float, 2> filter_z;

    static bool connected;

    static vect_t<float> accel_filtered;

public:
    static void begin(){
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write(0); // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
        connected = true;

        float b[] = {0.06745527, 0.13491055, 0.06745527};
        float a[] = {-1.1429805,  0.4128016};

        filter_x.setCoefficients(b, a);
        filter_y.setCoefficients(b, a);
        filter_z.setCoefficients(b, a);

    }

    static void task_read(void *pvParameters);

    static void read();

    static vect_t<float> getAccel(void) {return accel_filtered;}

    static String getFormatted();

    static void printFormatted(void);

    ~MPU6050(){Wire.endTransmission(true);};
};

extern MPU6050 mpu;