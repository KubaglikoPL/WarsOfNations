#pragma once

#include <stdint.h>

#define Texture uint32_t

typedef struct gl2Buffers {
	uint32_t VBO;
	uint32_t EBO;
	uint32_t VBO_Size;
	uint32_t EBO_Size;
	bool shortIndicies;
} gl2Buffers_t;

typedef struct glRenderer {
	uint32_t activeTexture;
	uint32_t activeVBO;
	uint32_t activeEBO;
	uint32_t activeProgram;
} glRenderer_t;

#define Renderer glRenderer_t
#define Buffer gl2Buffers_t
