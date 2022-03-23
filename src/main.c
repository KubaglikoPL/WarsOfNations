#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include <ui/game_ui.h>
#include <network/server_client.h>
#include <game/map_generator.h>
#include <framework/texture.h>
#include <framework/window.h>

void mainLoop();

bool running = true;
Window* window = NULL;
Renderer renderer = NULL;

generatorSettings generator_settings;
generatedMap map;
gameServer server;
gameClient client;

int main() {
	//Initialization
	window = createWindow("Walki Krajuw", 1280, 720);
	renderer = createRenderer(window);
	//ui_init(window, renderer);
	initSocketApi();
	server = createGameServer();
	client = createGameClient();
	generator_settings.frequency = 1.0f;
	generator_settings.gain = 0.5f;
	generator_settings.lacunarity = 2.0f;
	generator_settings.octaves = 8;
	generator_settings.strenght = 1.0f;
	generateMap(&map, &generator_settings, 80, 60);
	loadMap(&map, map.width, map.height, map.tileData);

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
	//ui_beginInput();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				running = false;
			}
		}
		//ui_processEvent(&event);
	}
	//ui_endInput();

	if (server.serverPort != 0) updateServer(&server);
	if (client.connected) updateClient(&client);

	//ui_newFrame();
	clearWindow(renderer, 0, 0, 255, 255);
	if (map.texture) SDL_RenderCopy(renderer, map.texture, NULL, NULL);

	//ui_main();
	//ui_render();

	display(renderer);
}
