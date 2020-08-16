#include <task_accel.hpp>

MPU6050 mpu;

void TaskAccel(void *pvParameters){
    (void) pvParameters;

    mpu.begin();

    while (1){
        xSemaphoreTake(xSemaphore_Button1, portMAX_DELAY);
        Serial.println(mpu.getFormatted());
        vTaskDelay(100/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Accel: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}

