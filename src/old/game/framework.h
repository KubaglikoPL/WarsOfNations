#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

typedef struct {
	uint32_t id;
	uint32_t x, y, w, h;
} subTexture;

typedef struct {
	uint32_t size;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
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

texture createTexture(SDL_Renderer *renderer, uint32_t size);
bool loadTextures(texture *texture, textureLoadInfo *loadInfos, uint32_t loadInfosAmount);
txCoord getTextureCoords(texture* texture, uint32_t subTextureID, uint32_t x, uint32_t y);
subTexture getSubTexture(texture* texture, uint32_t subTextureID);