#include <MPU6050.hpp>
#include <Arduino_FreeRTOS.h>

const int MPU6050::MPU_addr=0x68;
const int16_t MPU6050::LSB_g = 16384;
const int MPU6050::read_delay = 50;


// define vectors
vect_t<int16_t> MPU6050::accel;
vect_t<float> MPU6050::accel_filtered;
vect_t<int16_t> MPU6050::gyro;

Filter<float, 2> MPU6050::filter_x;
Filter<float, 2> MPU6050::filter_y;
Filter<float, 2> MPU6050::filter_z;

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
        begin();
        delay(1000/portTICK_PERIOD_MS);
    }

    while(1){
        read();

        accel_filtered.x = filter_x.process(accel.x);
        accel_filtered.y = filter_y.process(accel.y);
        accel_filtered.z = filter_z.process(accel.z);

        accel_filtered.calcPolar();

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

    ret += accel_filtered.x;
    ret += "," + String(accel_filtered.y);
    ret += "," + String(accel_filtered.z);

    ret += "\t\t\t|\t";

    ret += String(accel_filtered.theta);
    ret += "," + String(accel_filtered.phi);

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