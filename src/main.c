#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "ui/ui.h"
#include <game/server_client.h>
#include <game/map_generator.h>

void mainLoop();

bool running = true;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

generatorSettings generator_settings;
generatedMap map;
gameServer server;
gameClient client;

int main() {
	//Initialization
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	window = SDL_CreateWindow("Walki Krajuw", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	ui_init(window, renderer);
	init_socket_api();
	server = createGameServer();
	client = createGameClient();

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
		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				running = false;
			}
		}
		ui_processEvent(&event);
	}
	ui_endInput();

	if (server.serverPort != 0) updateServer(&server);
	if (client.connected) updateClient(&client);

	ui_newFrame();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	if(map.texture) SDL_RenderCopy(renderer, map.texture, NULL, NULL);

	ui_main();
	ui_render();

	SDL_RenderPresent(renderer);
}
