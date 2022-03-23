#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <framework/renderer.h>

typedef struct {
	float frequency;
	int32_t octaves;
	float gain;
	float lacunarity;
	float strenght;
} generatorSettings;

#pragma pack(push, 1)
typedef struct {
	bool water;
	uint8_t r;
	uint8_t g;
	uint8_t b;
} mapTile;
#pragma pack(pop)

typedef struct {
	uint32_t width;
	uint32_t height;

	uint32_t tx_width;
	uint32_t tx_height;
	SDL_Texture* texture;

	mapTile* tileData;
} generatedMap;

generatedMap createGeneratedMap();
void generateMap(generatedMap* map, generatorSettings* settings, uint32_t width, uint32_t height);
void loadMap(generatedMap* map, uint32_t width, uint32_t height, mapTile* tileData);
