#include "ui.h"
#define NK_IMPLEMENTATION
#include <nuklear.h>
#define NK_SDL_RENDERER_IMPLEMENTATION
#include <nuklear_sdl_renderer.h>

UI_STATE uiState = UI_STATE_INIT;

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

#include <game/protocol.h>
#include <game/server_client.h>

char ipBuffer[128] = {NULL};
char portBuffer[6] = {NULL};
char portBuffer2[6] = {NULL};
char widthBuffer[6] = {'6', '0', NULL };
char heightBuffer[6] = {'4', '0', NULL };
char usernameBuffer[USERNAME_MAX_LENGHT];
uint16_t port;
uint32_t mapWidth;
uint32_t mapHeight;
bool mapAutoGenerate = false;

#define NUMBER_INPUT_BUFFER_SIZE 16

#include <game/map_generator.h>
#include <stdbool.h>

extern generatorSettings generator_settings;
extern generatedMap map;
bool settingsInitialized = false;

void ui_generatorSetting();
void ui_host();
void ui_join();

void ui_main() {
	if (uiState == UI_STATE_INIT) {
		ui_join();
		ui_host();
		ui_generatorSetting();
	}
	else if (uiState == UI_STATE_HOSTING) {

	}
}

void ui_generatorSetting() {
	if (!settingsInitialized) {
		generator_settings.frequency = 0.1f;
		generator_settings.gain = 0.5f;
		generator_settings.lacunarity = 2.0f;
		generator_settings.octaves = 3;
		generator_settings.strenght = 1.0f;
		settingsInitialized = true;
	}
	if (nk_begin(ctx, "Generator", nk_rect(600, 0, 350, 300),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Frequency:", NK_TEXT_ALIGN_LEFT);
		generator_settings.frequency = nk_slide_float(ctx, 0.05f, generator_settings.frequency, 2.0f, 0.05f);

		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Octaves:", NK_TEXT_ALIGN_LEFT);
		generator_settings.octaves = nk_slide_int(ctx, 1, generator_settings.octaves, 8, 1);

		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Gain:", NK_TEXT_ALIGN_LEFT);
		generator_settings.gain = nk_slide_float(ctx, 0.2f, generator_settings.gain, 1.0f, 0.05f);

		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Lacunarity:", NK_TEXT_ALIGN_LEFT);
		generator_settings.lacunarity = nk_slide_float(ctx, 1.0f, generator_settings.lacunarity, 5.0f, 0.05f);

		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Strenght:", NK_TEXT_ALIGN_LEFT);
		generator_settings.strenght = nk_slide_float(ctx, 0.1f, generator_settings.strenght, 2.0f, 0.05f);
		
		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Width:", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, widthBuffer, 6, nk_filter_default);

		nk_layout_row_dynamic(ctx, 20, 2);
		nk_label(ctx, "Height:", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, heightBuffer, 6, nk_filter_default);

		nk_layout_row_dynamic(ctx, 20, 1);
		mapAutoGenerate = nk_check_label(ctx, "Auto Generate", mapAutoGenerate);
		mapWidth = atoi(widthBuffer);
		mapHeight = atoi(heightBuffer);

		nk_layout_row_dynamic(ctx, 20, 1);
		if (nk_button_label(ctx, "Generate") || mapAutoGenerate) {
			generateMap(&map, &generator_settings, mapWidth, mapHeight);
		}
	}
	nk_end(ctx);
}

extern gameServer server;

void ui_host() {
	if (nk_begin(ctx, "Host", nk_rect(300, 0, 300, 200),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "Port:", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, portBuffer2, 6, nk_filter_default);
		nk_layout_row_dynamic(ctx, 30, 1);
		uint16_t port = atoi(portBuffer2);
		if (nk_button_label(ctx, "Host")) {
			initGameServer(&server, port);
			uiState = UI_STATE_HOSTING;
		}
	}
	nk_end(ctx);
}

void ui_join() {
	if (nk_begin(ctx, "Join", nk_rect(0, 0, 300, 200),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "IP:", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, ipBuffer, 128, nk_filter_default);
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "Port:", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, portBuffer, 6, nk_filter_default);
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "Username:", NK_TEXT_ALIGN_LEFT);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, usernameBuffer, USERNAME_MAX_LENGHT, nk_filter_default);
		if (nk_button_label(ctx, "Connect")) {

		}
	}
	nk_end(ctx);
}
