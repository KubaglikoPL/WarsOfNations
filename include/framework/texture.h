#pragma once

#include <platform/platform.h>

typedef struct texCoords {
	float xf, yf, wf, hf;
} texCoords_t;

typedef struct subTexture {
	uint32_t ID;
	uint32_t x, y, w, h;
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

fwTexture_t loadTexture(Renderer *renderer, textureLoadInfo_t* loadInfos, uint32_t loadInfosAmount, uint32_t size);
fwTexture_t loadSingleTexture(Renderer *renderer, const char* filepath);
texCoords_t getTexCoord(fwTexture_t* texture, uint32_t subTexture, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
