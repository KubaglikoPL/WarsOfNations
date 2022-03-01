#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "ui/ui.h"

void mainLoop();

bool running = true;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main() {
	//Initialization
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	window = SDL_CreateWindow("Walki Krajuw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	ui_init(window, renderer);

	//Main loop
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(mainLoop, 0, false);
#else
	while (running) mainLoop();
#endif //__EMSCRIPTEN__
	return 0;
}

void mainLoop() {
	SDL_Event event;
	ui_beginInput();
	while (SDL_PollEvent(&event)) {
		ui_processEvent(&event);
	}
	ui_endInput();
	ui_newFrame();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);

	ui_main();
	ui_render();

	SDL_RenderPresent(renderer);
}
