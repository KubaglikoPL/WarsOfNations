#include <stdbool.h>
#include <engine/engine.h>

void mainLoop();

bool running = true;

int main() {
	//Initialization
	ge_engine_t* engine = createEngine();

	//Main loop
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(mainLoop, 0, false);
#else
	while (running) mainLoop();
#endif //__EMSCRIPTEN__
	return 0;
}

void mainLoop() {
	
}
