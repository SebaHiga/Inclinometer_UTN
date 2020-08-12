#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <vector.hpp>

class MPU6050{
private:
    const int MPU_addr=0x68;
    const int16_t LSB_g = 16384;
    
    // define vectors
    vect_t<int16_t> accel;
    vect_t<int16_t> gyro;

public:
    void begin(){
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write(0); // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
    }

    void read(){
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr,14,1); // request a total of 14 registers

        int16_t data_raw[14];
        int16_t data[7];

        for(auto &val : data_raw){
            val = Wire.read();
        }

        int i = 0;
        for(auto &val : data){
            val = data_raw[i] << 8 | data_raw[i + 1];
            i += 2;
        }

        accel = data;
        gyro = data + 4;

        Wire.endTransmission(true);
    };

    inline String getFormatted() const{
        String ret;

        vect_t<float> accel_float;

        accel_float = accel;
        accel_float /= LSB_g;
        accel_float *= 10;

        ret += accel_float.x;
        ret += "\t" + String(accel_float.y);
        ret += "\t" + String(accel_float.z);

        return ret;
    }

    inline void printFormatted(void){
        vect_t<float> accel_float;

        accel_float = accel;
        accel_float /= LSB_g;
        accel_float *= 10;

        Serial.print("\n");
        Serial.print(accel_float.x, 6); Serial.print(", ");
        Serial.print(accel_float.y, 6); Serial.print(", ");
        Serial.print(accel_float.z, 6);
    }

    ~MPU6050(){Wire.endTransmission(true);};
};
