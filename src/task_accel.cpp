#include <task_accel.hpp>


void TaskAccel(void *pvParameters){
    (void) pvParameters;

    MPU6050 mpu;

    mpu.begin();

    while (1){
        mpu.read();
        Serial.println(mpu.getFormated());

        delay(200);
    }
}