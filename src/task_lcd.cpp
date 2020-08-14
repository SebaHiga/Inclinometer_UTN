#include <task_lcd.hpp>

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void TaskLCD(void *pvParameters){
    (void) pvParameters;

    lcd.begin(COLUMS, ROWS);

    lcd.print(F("Hola Meli <3"));

    while(1){
        vTaskDelay(200/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task LCD: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}

