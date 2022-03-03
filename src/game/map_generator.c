#include "map_generator.h"
#define FNL_IMPL
#include <FastNoiseLite.h>
#include <malloc.h>

generatedMap createGeneratedMap() {
	generatedMap m;
	m.data = NULL;
	m.dataSize = 0;
	m.height = 0;
	m.width = 0;
	m.tx_width = 0;
	m.tx_height = 0;
	m.texture = NULL;
	return m;
}

extern SDL_Renderer* renderer;

void generateMap(generatedMap* map, generatorSettings* settings, uint32_t width, uint32_t height) {
	fnl_state state = fnlCreateState();
	state.frequency = settings->frequency;
	state.octaves = settings->octaves;
	state.gain = settings->gain;
	state.lacunarity = settings->lacunarity;
	state.fractal_type = FNL_FRACTAL_FBM;
	uint32_t mapSize = width * height * sizeof(float);
	map->width = width;
	map->height = height;
	if (map->dataSize < mapSize) {
		map->dataSize = mapSize;
		map->data = realloc(map->data, mapSize);
	}
	if ((map->tx_width != map->width) || (map->tx_height != map->height)) {
		if (map->texture) SDL_DestroyTexture(map->texture);
		map->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, map->width, map->height);
		map->tx_width = map->width;
		map->tx_height = map->height;
	}
	uint32_t i = 0;
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			float n = fnlGetNoise2D(&state, x / 10.0f, y / 10.0f);
			n = (n + 1.0f) / 2.0f;
			n = n * settings->strenght;
			n = fminf(n, 1.0f);
			map->data[i] = n;
			i++;
		}
	}
	SDL_Rect updateRect;
	updateRect.x = 0;
	updateRect.y = 0;
	updateRect.w = map->width;
	updateRect.h = map->height;

	SDL_Color* updateData = alloca(map->width * map->height * 4);
	uint32_t updatePitch = map->width * 4;

	for (uint32_t i = 0; i < (width * height); i++) {
		updateData[i].r = (map->data[i] * 255.0f);
		updateData[i].g = 0;
		updateData[i].b = 0;
		updateData[i].a = 255;
	}

	SDL_UpdateTexture(map->texture, &updateRect, updateData, updatePitch);
}
