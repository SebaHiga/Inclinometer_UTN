#include <task_lcd.hpp>
#include <global.hpp>
#include <LiquidCrystal_I2C.h>
#include <stdlib.h>
// LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

extern vect_t<float> accel_filtered;

class LCD : public LiquidCrystal_I2C
{
public:
    enum Line : uint8_t{
        First = 0,
        Second
    };

   LCD(uint8_t P0 = 4, uint8_t P1 = 5, 
            uint8_t P2 = 6, uint8_t P3 = 16, uint8_t P4 = 11, uint8_t P5 = 12, uint8_t P6 = 13,
            uint8_t P7 = 14, backlightPolarity = POSITIVE) :
    LiquidCrystal_I2C(PCF8574_ADDR_A21_A11_A01, P0, P1, P2, P3, P4, P5, P6, P7){
        clear();
    }

    void clear() {
        for (size_t row = 0; row < 2; row++) {
            for (size_t index = 0; index < 16; index++) {
                m_lineMatrix[row][index] = ' ';
            }
        }   
    }

    void printDiff(Line line, const char *str){
        for(size_t i = 0; i < 16; i++){
            delay(10);
            if (m_lineMatrix[line][i] != str[i]) {
                m_lineMatrix[line][i] = str[i];
                
                setCursor(i, line);
                delay(10);

                if (str[i] == '\0') {
                    write(' ');
                }
                else{
                    write(str[i]);
                }

                delay(10);
            }
        }
    }

private:
    char m_lineMatrix[2][16];
};

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

        auto angle = ceil(Global::angle);

        int bubbleIndex = 7 + ((float)7/90) * angle;

        row2[bubbleIndex] = 'O';

        offset = angle >= 0 ? 1 : 0;

        itoa(angle, row1+5+offset, 10);
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

