#pragma once

#include <main.hpp>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void TaskLCD(void *pvParameters);

#define COLUMS 16
#define ROWS   2