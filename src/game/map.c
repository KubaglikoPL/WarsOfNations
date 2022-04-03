#include <game/map.h>
#include <malloc.h>
#define FNL_IMPL
#include <FastNoiseLite.h>
#include <stb_image.h>

uint8_t* terrainTextureData;
uint32_t terrainTextureWidth;

void loadTerrainTexture(const char* filepath) {
	int x, y, comp;
	terrainTextureData = stbi_load(filepath, &x, &y, &comp, 4);
	terrainTextureWidth = x;
}

map_t createMap(void) {
	map_t m;
	m.h = 0;
	m.w = 0;
	m.resources = NULL;
	m.resourcesAmount = 0;
	m.resourcesSize = 0;
	m.tiles = NULL;
	m.tilesSize = 0;
	return m;
}

mapTexture_t createMapTexture(void) {
	mapTexture_t m;
	m.tx_w = 0;
	m.tx_h = 0;
	m.texture = NULL;
	return m;
}

void generateMap(map_t* map, mapGenerator_t* settings) {
	map->w = settings->w;
	map->h = settings->h;
	uint32_t tilesSize = map->w * map->h;
	if (tilesSize > map->tilesSize) {
		map->tiles = realloc(map->tiles, tilesSize * sizeof(tile_t));
		map->tilesSize = tilesSize;
	}

	fnl_state noiseState = fnlCreateState();

	uint32_t i = 0;
	for (uint32_t x = 0; x < map->w; x++) {
		for (uint32_t y = 0; y < map->h; y++) {
			float n = fnlGetNoise2D(&noiseState, x, y);
			n = (n + 1.0f) / 2.0f;
			map->tiles[i].height = (n * UINT16_MAX);
			map->tiles[i].flags = 0;
			map->tiles[i].player = 0;
			i++;
		}
	}
}

void updateMapTexture(Renderer* renderer, mapTexture_t* texture, map_t* map) {
	if ((map->w != texture->tx_w) || (map->h != texture->tx_h)) {
		if (texture->texture) destroyTexture(&texture);
		texture = createTexture(renderer, map->w, map->h);
		texture->tx_w = map->w;
		texture->tx_h = map->h;
	}
	uint32_t* textureData = alloca(map->w * map->h * sizeof(uint32_t));
	uint32_t i = 0;
	for (uint32_t x = 0; x < map->w; x++) {
		for (uint32_t y = 0; y < map->h; y++) {
			uint8_t* color = (uint8_t*)&textureData[i];
			
			uint8_t* tcolor = &terrainTextureData[i * 4];

			color[0] = tcolor[0];
			color[1] = tcolor[1];
			color[2] = tcolor[2];
			color[3] = tcolor[3];

			i++;
		}
	}
	updateTexture(renderer, &texture->texture, 0, 0, map->w, map->h, textureData);
}
