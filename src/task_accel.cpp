#include <task_accel.hpp>


void TaskAccel(void *pvParameters){
    (void) pvParameters;

    MPU6050 mpu;

    mpu.begin();

    while (1){
        mpu.read();
        Serial.println(mpu.getFormated());

        delay(200);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Accel: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}