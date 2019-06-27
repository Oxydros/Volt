#pragma once

#include "Volt/Logger.hpp"

#include <cassert>

#if VOLT_DEBUG
    #define VOLT_ASSERT(cond, ...) { if (!(cond)) {VOLT_ERROR("Assertion failed !");VOLT_ERROR(__VA_ARGS__); assert(false);}}
#else
    #define VOLT_ASSERT(cond, ...)
#endif