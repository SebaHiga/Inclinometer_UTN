#pragma once

#include <main.hpp>
#include "semphr.h"

namespace Global{

extern double angle;
extern double offset;
extern bool buttonOffset;

extern SemaphoreHandle_t  mutex_angle;

} // namespace