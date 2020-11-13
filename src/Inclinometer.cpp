#include <Inclinometer.hpp>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <global.hpp>

MPU6050 Inclinometer::mpu;

void Inclinometer::run(void *pvParameters){
    (void) pvParameters;

    while (1){
        auto accel = mpu.getAccel();
        auto x = accel.x;
        auto z = accel.z;

        auto lambda = ((asin(x/sqrt(x*x + z*z)))*180) / M_PI;

        Global::angle = lambda - Global::offset;

        if (Global::buttonOffset) {
            Global::offset = lambda;
        }

        // Serial.println(lambda, 2);

        vTaskDelay(1000/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Inclinometer: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}
