#include <main.hpp>
#include <global.hpp>

double Global::angle = 0;
double Global::offset = 0;
bool Global::buttonOffset = false;

SemaphoreHandle_t  Global::mutex_angle;