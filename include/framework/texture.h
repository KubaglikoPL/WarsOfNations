#pragma once

#include "renderer.h"

#define Texture SDL_Texture*
Texture createTexture(uint32_t w, uint32_t h);
void updateTexture(Renderer renderer, Texture texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data);

typedef struct {
	uint32_t id;
	uint32_t x, y, w, h;
} subTexture;

typedef struct {
	uint32_t size;
	Texture texture;
	Renderer renderer;
	subTexture* subTextures;
	uint32_t subTexturesAmount;
} texture;

typedef struct {
	uint32_t id;
	const char* file;
} textureLoadInfo;

typedef struct {
	float x;
	float y;
	float w;
	float h;
} txCoord;

texture createTexture2(Renderer *renderer, uint32_t size);
bool loadTextures(texture *texture, textureLoadInfo *loadInfos, uint32_t loadInfosAmount);
txCoord getTextureCoords(texture* texture, uint32_t subTextureID, uint32_t x, uint32_t y);
subTexture getSubTexture(texture* texture, uint32_t subTextureID);