#pragma once

#include <stdint.h>

// Version Major change . Incompatable change . Fixes . Build increment

#define VER_STR "0.0.1.000"
#define VER_MAJOR 0
#define VER_MINOR 0
#define VER_PATCH 1
#define VER_BUILD 000
#define VER (uint32_t)(VER_MAJOR << 24 | VER_MINOR << 16 & VER_PATCH << 8 & VER_BUILD << 0)
