#include <task_lcd.hpp>

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

extern vect_t<float> accel_filtered;
extern float angle;

void TaskLCD(void *pvParameters){
    (void) pvParameters;

    lcd.begin(COLUMS, ROWS);

    while(1){
        lcd.clear();
        lcd.home();
        lcd.print(angle);
        vTaskDelay(500/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task LCD: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}

