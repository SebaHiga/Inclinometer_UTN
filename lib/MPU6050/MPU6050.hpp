#include <Arduino.h>
#include <Wire.h>

#pragma once

class MPU6050{
private:
    const int MPU_addr=0x68;
    
    typedef struct _rawVect_t{
        union{
            struct{
                int16_t xyz[3];
            };
            struct{
                int16_t x, y, z;
            };
        };

        template<typename T>
        void operator= (const T vec){
            int i = 0;
            for(auto &val : xyz){
                val = vec[i];
                i++;
            }
        }
    }rawVect_t;

    // define vectors
    rawVect_t accel;
    rawVect_t gyro;

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

    inline String getFormated(){
        String ret;

        ret += accel.x;
        ret += "\t" + String(accel.y);
        ret += "\t" + String(accel.z);

        return ret;
    }

    ~MPU6050(){Wire.endTransmission(true);};
};
