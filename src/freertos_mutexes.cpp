#include <freertos_mutexes.hpp>
#include <main.hpp>


SemaphoreHandle_t xSemaphore_Button1;

void create_semaphores(){
    xSemaphore_Button1 = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore_Button1);
}