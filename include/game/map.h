#pragma once

#include <stdint.h>

#define TILE_WATER 1
#define TILE_RESOURCE 2
#define TILE_CITY 4
#define TILE_UNIT 8

#pragma pack(push, 1)
typedef struct tile {
	uint16_t height;
	uint8_t flags;
	uint8_t player;
} tile_t;
#pragma pack(pop)

typedef struct mapResource {
	uint16_t x, y;
	uint32_t type;
} mapResource_t;

typedef struct map {
	uint16_t w, h;

	uint32_t tilesSize;
	tile_t* tiles;

	uint32_t resourcesSize;
	uint32_t resourcesAmount;
	mapResource_t* resources;
} map_t;

typedef struct mapGenerator {
	uint16_t w, h;
} mapGenerator_t;

#include <platform/platform.h>

typedef struct mapTexture {
	uint16_t tx_w, tx_h;
	Texture texture;
} mapTexture_t;

void loadTerrainTexture(const char *filepath);
map_t createMap(void);
mapTexture_t createMapTexture(void);
void generateMap(map_t* map, mapGenerator_t *settings);
void updateMapTexture(Renderer *renderer, mapTexture_t* texture, map_t* map);
