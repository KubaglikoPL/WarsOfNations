#pragma once

#include <SDL.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

void ui_init(SDL_Window* window, SDL_Renderer* renderer);

void ui_newFrame();
void ui_beginInput();
void ui_processEvent(SDL_Event* event);
void ui_endInput();
void ui_render();

void ui_main();