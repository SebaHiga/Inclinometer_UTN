#include <task_accel.hpp>

static MPU6050 mpu;

void TaskAccel(void *pvParameters){
    (void) pvParameters;


    mpu.begin();

    
    xTaskCreate(mpu.task_read,
        "Read MPU constantly",
        126,
        NULL, 
        1,
        NULL );

    while (1){
        xSemaphoreTake(xSemaphore_Button1, portMAX_DELAY);
        mpu.read();
        mpu.printFormatted();
        vTaskDelay(1);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Accel: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}