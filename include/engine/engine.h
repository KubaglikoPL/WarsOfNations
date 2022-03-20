#pragma once

#include <export.h>
#include <stdint.h>

#define ENGINE_VERSION 1
#define ENGINE_COMPATIBILITY_VERSION 1

typedef struct ge_engine {
	uint32_t (*version)(void);
	uint32_t (*compatibilityVersion)(void);
} ge_engine_t;

API ge_engine_t* createEngine();