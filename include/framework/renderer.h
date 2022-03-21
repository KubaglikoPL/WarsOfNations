#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "window.h"

#define Renderer SDL_Renderer*

Renderer createRenderer(Window window);
void clearWindow(Renderer renderer, uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void display(Renderer renderer);