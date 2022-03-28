#pragma once

#include <stdint.h>

#define TILE_WATER 1
#define TILE_RESOURCE 2
#define TILE_CITY 4
#define TILE_UNIT 8

#pragma pack(push, 1)
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t flags;
	uint8_t player;
} tile;
#pragma pack(pop)

typedef struct {
	uint16_t x, y;
	uint32_t type;
} mapResource;

typedef struct {
	uint16_t w, h;

	uint32_t tilesSize;
	tile* tiles;

	uint32_t resourcesSize;
	uint32_t resourcesAmount;
	mapResource* resources;
} map;
