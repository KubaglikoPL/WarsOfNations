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

typedef struct glShader {
	uint32_t program;
	int32_t texture0_location;
	int32_t VP_location;
} glShader_t;

#define Renderer glRenderer_t
#define Buffer gl2Buffers_t
#define Shader glShader_t
