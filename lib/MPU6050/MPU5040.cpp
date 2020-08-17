#include <MPU6050.hpp>
#include <Arduino_FreeRTOS.h>

const int MPU6050::MPU_addr=0x68;
const int16_t MPU6050::LSB_g = 16384;
const int MPU6050::read_delay = 10;


// define vectors
vect_t<int16_t> MPU6050::accel;
vect_t<int16_t> MPU6050::gyro;

Filter<int16_t, 3> MPU6050::filter;


bool MPU6050::connected = false;

void MPU6050::read(){
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

void  MPU6050::task_read(void *pvParameters){
    while(!connected){
        delay(1000/portTICK_PERIOD_MS);
    }

    while(1){
        read();
        Serial.println(filter.process(accel.x));
        vTaskDelay(read_delay/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Read accel: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}

String MPU6050::getFormatted(){
    String ret;

    ret += accel.x;
    ret += "," + String(accel.y);
    ret += "," + String(accel.z);

    return ret;
}

void MPU6050::printFormatted(void){
    vect_t<float> accel_float;

    accel_float = accel;
    accel_float /= LSB_g;
    accel_float *= 10;

    Serial.print("\n");
    Serial.print(accel_float.x, 6); Serial.print(", ");
    Serial.print(accel_float.y, 6); Serial.print(", ");
    Serial.print(accel_float.z, 6);
}