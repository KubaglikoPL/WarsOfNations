#pragma once

#include <SDL.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS

void ui_init(SDL_Window* window, SDL_Renderer* renderer);

void ui_newFrame();
void ui_beginInput();
void ui_processEvent(SDL_Event* event);
void ui_endInput();
void ui_render();

typedef enum {
	UI_STATE_INIT = 0,
	UI_STATE_HOSTING = 1,
	UI_STATE_CONNECTED = 2,
	UI_STATE_GAME = 3
} UI_STATE;

extern UI_STATE uiState;

void ui_main();

//UI functions
//void ui_selectCapital();
