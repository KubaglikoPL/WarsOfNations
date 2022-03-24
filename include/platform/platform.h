#pragma once

#include <stdint.h>
#include <stdbool.h>

#if 0

#else
	#include "platform_glfw.h"
	#include "platform_miniaudio.h"
	#include "platform_gl2.h"
	#define PLATFORM_GLFW_IMPL	
	#define PLATFORM_MINIAUDIO_IMPL
	#define PLATFORM_GL2_IMPL
#endif

//Window, Events and stuff
bool initPlatform(void);

Window createWindow(const char* title, uint32_t w, uint32_t h);
bool isWindowOpen(Window window);
void windowDisplay(Window window);
void windowPollEvents(Window window);
//Rendering
Renderer createRenderer(Window window);

Texture createTexture(Renderer renderer, uint32_t w, uint32_t h);
void destroyTexture(Texture texture);
void updateTexture(Renderer renderer, Texture texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data);

void rendererClear(Renderer renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
//Audio
bool initAudio(void);