#pragma once

#include <Arduino.h>
#include <Wire.h>

class MPU6050{
private:
    const int MPU_addr=0x68;
    
    template<typename T>
    struct vect_t{
        union{
            struct{
                T xyz[3];
            };
            struct{
                T x, y, z;
            };
        };

        template<typename P>
        void operator= (const P vec){
            int i = 0;
            for(auto &val : xyz){
                val = (T) vec[i];
                i++;
            }
        }

        T operator[] (size_t index) const {
            return xyz[index];
        }

        template<typename P>
        void operator/= (const P num){
            int i = 0;
            for(auto &val : xyz){
                val = (T) (val / num);
                i++;
            }
        }

        template<typename P>
        void operator*= (const P num){
            int i = 0;
            for(auto &val : xyz){
                val = (T) (val * num);
                i++;
            }
        }

        float getModule (){
            return sqrt(x*x + y*y + z*z);
        }

    };

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

    inline String getFormated(){
        String ret;

        ret += accel.x;
        ret += "\t" + String(accel.y);
        ret += "\t" + String(accel.z);

        return ret;
    }

    ~MPU6050(){Wire.endTransmission(true);};
};
