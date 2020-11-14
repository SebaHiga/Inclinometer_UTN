#include <Inclinometer.hpp>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <global.hpp>
#include <vector.hpp>

MPU6050 Inclinometer::mpu;

void Inclinometer::run(void *pvParameters){
    (void) pvParameters;

    using Module = vect_t<float>::Module;

    while (1){
        auto accel = mpu.getAccel();
        auto moduleXZ = accel.getModule(Module::xz);
        auto moduleYZ = accel.getModule(Module::yz);
        auto x = accel.x;
        auto y = accel.y;
        auto z = accel.z;

        double lambda;
        
        if (moduleXZ > moduleYZ) {
            lambda = ((atan(x / z))*180) / M_PI;
        }
        else {
            lambda = ((atan(y / z))*180) / M_PI;
        }


        Global::angle = lambda * 1.1984868395599182-0.37193951653249635;

        if (Global::buttonOffset) {
            Global::offset = Global::angle;
        }

        Global::angle -= Global::offset;

        // Serial.println(lambda, 2);

        vTaskDelay(250/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Inclinometer: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}
