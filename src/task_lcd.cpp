#include <task_lcd.hpp>
#include <global.hpp>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
// LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

extern vect_t<float> accel_filtered;

LCD lcd;

#define BUBBLE_BASE "[==============]"

void TaskLCD(){
    int val = 100;
    int offset = 0;
    char row1[16] = {' '};
    char row2[16] = {' '};

    while(1){
        val += 6;

        memset(row1, ' ', 16);
        strcpy(row2, BUBBLE_BASE);

        int angle;
        
        if (Global::angle < 0.5 and Global::angle > -0.5) {
            angle = 0;
        }
        else {
            angle = Global::angle > 0 ? ceil(Global::angle) : floor(Global::angle);
        }

        int bubbleIndex = 7 + ((7*angle)/45);

        bubbleIndex = bubbleIndex < 1 ? 1 : (bubbleIndex > 13 ? 13 : bubbleIndex);

        row2[bubbleIndex] = '(';
        row2[bubbleIndex+1] = ')';

        offset = angle >= 0 ? 1 : 0;

        itoa(angle, row1+6+offset, 10);
        strcat(row1, " deg");

        if (angle > 90 or angle < -90) {
            strcpy(row1, "       Err      ");
        }

        // lcd.clear();
        // Serial.println(angle);
        // lcd.print((float) angle);
        lcd.printDiff(LCD::Line::First, row1);
        lcd.printDiff(LCD::Line::Second, row2);
        delay(10);
        // vTaskDelay(500/portTICK_PERIOD_MS);

        #ifdef FREERTOS_STACKDEBUG
        UBaseType_t uxHighWaterMark;
        /* Inspect our own high water mark on entering the task. */
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("\nFree stack - Task LCD: ");
        Serial.println(uxHighWaterMark);
        #endif
    }
}

