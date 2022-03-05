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

char ipBuffer[128] = "localhost";
char portBuffer[6] = "32333";
char portBuffer2[6] = "32333";
char widthBuffer[6] = "120";
char heightBuffer[6] = "80";
char usernameBuffer[USERNAME_MAX_LENGHT] = "Player1";
uint16_t port;
uint32_t mapWidth;
uint32_t mapHeight;
bool mapAutoGenerate = true;

#define NUMBER_INPUT_BUFFER_SIZE 16

#include <game/map_generator.h>
#include <stdbool.h>

extern generatorSettings generator_settings;
extern generatedMap map;
bool settingsInitialized = false;

void ui_generatorSetting();
void ui_host();
void ui_join();
void ui_hosting();
void ui_connected();

void ui_main() {
	if (uiState == UI_STATE_INIT) {
		ui_join();
		ui_host();
		ui_generatorSetting();
	}
	else if (uiState == UI_STATE_HOSTING) {
		ui_hosting();
		ui_generatorSetting();
	}
	else if (uiState == UI_STATE_CONNECTED) {
		ui_connected();
	}
}

void ui_generatorSetting() {
	if (!settingsInitialized) {
		generator_settings.frequency = 0.75f;
		generator_settings.gain = 0.4f;
		generator_settings.lacunarity = 3.0f;
		generator_settings.octaves = 5;
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
extern gameClient client;
bool selfConnect = true;

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

		nk_layout_row_dynamic(ctx, 20, 1);
		selfConnect = nk_check_label(ctx, "Self Connect", selfConnect);

		if (nk_button_label(ctx, "Host")) {
			initGameServer(&server, port);
			if (selfConnect) initGameClient(&client, port, "localhost", usernameBuffer);
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

		uint16_t port = atoi(portBuffer);

		if (nk_button_label(ctx, "Connect")) {
			initGameClient(&client, port, ipBuffer, usernameBuffer);
			uiState = UI_STATE_CONNECTED;
		}
	}
	nk_end(ctx);
}

bool serverSetuped = false;

void ui_hosting() {
	if (nk_begin(ctx, "Hosting", nk_rect(0, 0, 300, 200),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
			if (server.connections[i].connectionInfoReceived) {
				nk_layout_row_dynamic(ctx, 30, 1);
				if (server.connections[i].playerReady) {
					nk_labelf(ctx, NK_TEXT_ALIGN_LEFT, "%s(Ready)", server.connections[i].username);
				}
				else nk_label(ctx, server.connections[i].username, NK_TEXT_ALIGN_LEFT);
			}
		}

		nk_layout_row_dynamic(ctx, 30, 1);
		if (nk_button_label(ctx, "Start Game")) {
			if (!serverSetuped) {
				serverSetupGame(&server);
				serverSetuped = true;
			}
		}
	}
	nk_end(ctx);
}

void ui_connected() {
	if (nk_begin(ctx, "Hosting", nk_rect(0, 0, 300, 200),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 30, 1);
		nk_label(ctx, "Connected waiting for game to start", NK_TEXT_ALIGN_LEFT);

		nk_layout_row_dynamic(ctx, 30, 1);
		nk_check_label(ctx, "Tile Data", client.mapData1_received);
		
		nk_layout_row_dynamic(ctx, 30, 1);
		nk_check_label(ctx, "Other Map Data", client.mapData2_received);

		nk_layout_row_dynamic(ctx, 30, 1);
		nk_check_label(ctx, "Player Data", client.playerData_received);

		if (client.client_ready) {
			nk_layout_row_dynamic(ctx, 30, 1);
			nk_label(ctx, "Waiting for players", NK_TEXT_ALIGN_LEFT);
		}
	}
	nk_end(ctx);
}