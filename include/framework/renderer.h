#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "window.h"

#define Renderer SDL_Renderer*

#define Texture SDL_Texture*
Texture createTexture(Renderer renderer, uint32_t w, uint32_t h);
void updateTexture(Texture texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data);
void destroyTexture(Texture texture);

#pragma pack(push, 1)
typedef struct {
	float x;
	float y;
	uint16_t tx_x; //normalized
	uint16_t tx_y; //normalized
	uint8_t color[4]; //rgba
} vertex;
#pragma pack(pop)

Renderer createRenderer(Window window);
void clearWindow(Renderer renderer, uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void display(Renderer renderer);
void draw(Renderer renderer, Texture texture, vertex* vertices, uint32_t num_vertices, uint32_t *indices, uint32_t num_indices);
