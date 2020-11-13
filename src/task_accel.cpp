#include <task_accel.hpp>

// float angle;

// void TaskAccel(void *pvParameters){
//     (void) pvParameters;

//     mpu.begin();

//     while (1){

//         auto x = accel_filtered.x;
//         auto z = accel_filtered.z;

//         auto lambda = ((asin(x/sqrt(x*x + z*z)))*180) / M_PI;

//         angle = 1.1984868 * lambda - 0.371939;

//         Serial.println(angle, 2);

//         vTaskDelay(100/portTICK_PERIOD_MS);

//         #ifdef FREERTOS_STACKDEBUG
//         UBaseType_t uxHighWaterMark;
//         /* Inspect our own high water mark on entering the task. */
//         uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
//         Serial.print("\nFree stack - Task Accel: ");
//         Serial.println(uxHighWaterMark);
//         #endif
//     }
// }

