#pragma once

#include <platform/platform.h>

typedef struct subTexture {
	uint32_t ID;
	uint32_t x, y, w, h;
	float xf, yf, wf, hf;
} subTexture_t;

//FrameWork Texture
typedef struct fwTexture {
	Texture texture;
	uint32_t w, h;
	subTexture_t* subTextures;
	uint32_t num_subTextures;
} fwTexture_t;

typedef struct textureLoadInfo {
	const char* filepath;
	uint32_t ID;
} textureLoadInfo_t;

fwTexture_t loadTexture(Renderer renderer, textureLoadInfo_t* loadInfos, uint32_t loadInfosAmount, uint32_t size);
fwTexture_t loadSingleTexture(Renderer renderer, const char* filepath);
