#pragma once

#include <stdint.h>
#include <SDL.h>

typedef struct {
	float frequency;
	int32_t octaves;
	float gain;
	float lacunarity;
	float strenght;
} generatorSettings;

typedef struct {
	uint32_t width;
	uint32_t height;
	//float seaLevel;
	uint32_t dataSize;
	float* data;

	uint32_t tx_width;
	uint32_t tx_height;
	SDL_Texture* texture;
} generatedMap;

generatedMap createGeneratedMap();
void generateMap(generatedMap* map, generatorSettings* settings, uint32_t width, uint32_t height);
