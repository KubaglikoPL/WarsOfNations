#include "framework.h"

texture createTexture(SDL_Renderer* renderer, uint32_t size) {
	texture tx;
	tx.size = size;
	tx.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, size, size);
	tx.renderer = renderer;
	tx.subTextures = NULL;
	tx.subTexturesAmount = 0;
	return tx;
}

#include <stb_rect_pack.h>
#include <stb_image.h>
#include <string.h>

bool loadTextures(texture* texture, textureLoadInfo* loadInfos, uint32_t loadInfosAmount) {
	texture->texture = SDL_CreateTexture(texture->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, texture->size, texture->size);

	for (uint32_t i = 0; i < loadInfosAmount; i++) {
		textureLoadInfo info = loadInfos[i];
		int w, h, channels;
		stbi_info(info.file, &w, &h, &channels, 4);
		rects[i].x = 0;
		rects[i].y = 0;
		rects[i].w = w;
		rects[i].h = h;
		rects[i].was_packed = false;
		rects[i].id = i;
	}
	
	for (uint32_t i = 0; i < loadInfosAmount; i++) {
		textureLoadInfo info = loadInfos[i];
		int w, h, channels;
		void *data = stbi_load(info.file, &w, &h, &channels, 4);
		if (w && h && data) {
			SDL_Rect rect;
			rect.x = rects[i].x;
			rect.y = rects[i].y;
			rect.w = rects[i].w;
			rect.h = rects[i].h;
			SDL_UpdateTexture(texture, &rect, data, texture->size * sizeof(uint32_t));
			stbi_image_free(data);
		}
	}
}

txCoord getTextureCoords(texture* texture, uint32_t subTextureID, uint32_t x, uint32_t y) {
	txCoord tc;
	subTexture st = getSubTexture(texture, subTextureID);
	tc.x = x + st.x;
	tc.y = y + st.y;
	tc.x = tc.x / texture->size;
	tc.y = tc.y / texture->size;
	tc.w = st.w / texture->size;
	tc.h = st.h / texture->size;
	return tc;
}

subTexture getSubTexture(texture* texture, uint32_t subTextureID) {
	subTexture s;
	s.id = subTextureID;
	s.x = 0;
	s.y = 0;
	s.w = texture->size;
	s.h = texture->size;
	for (uint32_t i = 0; i < texture->subTexturesAmount; i++) {
		if (texture->subTextures[i].id == subTextureID) return texture->subTextures[i];
	}
	return s;
}
