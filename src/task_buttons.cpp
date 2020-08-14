#include <task_buttons.hpp>

void TaskButtons(void *pvParameters){
    (void) pvParameters;

    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_3, INPUT);


    while (1){
        if(digitalRead(BUTTON_1)){
            xSemaphoreGive(xSemaphore_Button1);
        }
        vTaskDelay(500/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task Buttons: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}