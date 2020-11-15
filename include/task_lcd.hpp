#pragma once

#include <main.hpp>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.hpp>

void TaskLCD();

#define COLUMS 16
#define ROWS   2

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

extern LCD lcd;