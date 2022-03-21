#include <framework/texture.h>
#include <framework/window.h>

Window createWindow(const char* name, uint32_t w, uint32_t h) {
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	return SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL);
}

Renderer createRenderer(Window window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}

void clearWindow(Renderer renderer, uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void display(Renderer renderer) {
	SDL_RenderPresent(renderer);
}

Texture createTexture(uint32_t w, uint32_t h) {
	
}

void updateTexture(Renderer renderer, Texture texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data) {

}
