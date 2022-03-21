#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#define Window SDL_Window*

Window createWindow(const char *name, uint32_t w, uint32_t h);
