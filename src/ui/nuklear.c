#include "ui.h"
#define NK_IMPLEMENTATION
#include <nuklear.h>
#define NK_SDL_RENDERER_IMPLEMENTATION
#include <nuklear_sdl_renderer.h>

struct nk_context *ctx;
struct nk_font_atlas* atlas;

void ui_init(SDL_Window* window, SDL_Renderer* renderer) {
	ctx = nk_sdl_init(window, renderer);
	nk_sdl_font_stash_begin(&atlas);
	nk_sdl_font_stash_end();
}

void ui_newFrame() {}
void ui_beginInput() { nk_input_begin(ctx); }
void ui_processEvent(SDL_Event* event) { nk_sdl_handle_event(event); }
void ui_endInput() { nk_input_end(ctx); }
void ui_render() { nk_sdl_render(NK_ANTI_ALIASING_ON); }

void ui_main() {
	if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_static(ctx, 30, 80, 1);
		nk_button_label(ctx, "button");
	}
	nk_end(ctx);
}