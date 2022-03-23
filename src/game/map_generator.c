#include <game/map_generator.h>
#define FNL_IMPL
#include <FastNoiseLite.h>
#include <malloc.h>

generatedMap createGeneratedMap() {
	generatedMap m;
	m.height = 0;
	m.width = 0;
	m.tx_width = 0;
	m.tx_height = 0;
	m.texture = NULL;
	m.tileData = NULL;
	return m;
}

extern SDL_Renderer* renderer;

void generateMap(generatedMap* map, generatorSettings* settings, uint32_t width, uint32_t height) {
	fnl_state state = fnlCreateState();
	state.noise_type = FNL_NOISE_VALUE_CUBIC;
	state.frequency = settings->frequency;
	state.octaves = settings->octaves;
	state.gain = settings->gain;
	state.lacunarity = settings->lacunarity;
	state.fractal_type = FNL_FRACTAL_FBM;
	uint32_t mapSize = width * height * sizeof(float);
	map->width = width;
	map->height = height;
	
	float* mapData = alloca(map->width * map->height * 4);

	//Generate Noise
	uint32_t i = 0;
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			float falloff_factor_x = (x / (float)width) * 2.0f - 1.0f;
			float falloff_factor_y = (y / (float)height) * 2.0f - 1.0f;
			float falloff_factor = fmaxf(fabsf(falloff_factor_x), fabsf(falloff_factor_y));
			falloff_factor = powf(falloff_factor, 5.0f);
			falloff_factor = 1.0f - falloff_factor;

			float n = fnlGetNoise2D(&state, x / 10.0f, y / 10.0f);
			n = (n + 1.0f) / 2.0f;
			n = n * settings->strenght;
			n = n * falloff_factor;
			n = fminf(n, 1.0f);
			mapData[i] = n;
			i++;
		}
	}

	map->tileData = realloc(map->tileData, map->width * map->height * sizeof(mapTile));

	SDL_Rect updateRect;
	updateRect.x = 0;
	updateRect.y = 0;
	updateRect.w = map->width;
	updateRect.h = map->height;

	for (uint32_t i = 0; i < (width * height); i++) {
		float n = mapData[i];
		map->tileData[i].g = 0;
		if (n > 0.5f) {
			map->tileData[i].r = (n * 255.0f);
			map->tileData[i].b = 0;
			map->tileData[i].water = false;
		}
		else {
			map->tileData[i].r = 0;
			map->tileData[i].b = 255;
			map->tileData[i].water = true;
		}
	}
}

void loadMap(generatedMap* map, uint32_t width, uint32_t height, mapTile* tileData) {
	SDL_Color* colorData = alloca(map->width * map->height * sizeof(SDL_Color));

	map->width = width;
	map->height = height;
	if(tileData != map->tileData) SDL_memcpy(map->tileData, tileData, map->width * map->height * sizeof(mapTile));

	uint32_t updatePitch = map->width * 4;
	SDL_Rect updateRect;
	updateRect.x = 0;
	updateRect.y = 0;
	updateRect.w = map->width;
	updateRect.h = map->height;

	if ((map->tx_width != map->width) || (map->tx_height != map->height)) {
		if (map->texture) destroyTexture(map->texture);
		map->texture = createTexture(renderer, map->width, map->height);
		map->tx_width = map->width;
		map->tx_height = map->height;
	}

	for (uint32_t i = 0; i < (width * height); i++) {
		colorData[i].r = map->tileData[i].r;
		colorData[i].g = map->tileData[i].g;
		colorData[i].b = map->tileData[i].b;
		colorData[i].a = 255;
	}

	updateTexture(map->texture, 0, 0, map->width, map->height, colorData);
}
