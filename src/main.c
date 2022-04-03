#include <platform/platform.h>
#include <stdio.h>
#include <framework/audio.h>
#include <framework/texture.h>
#include <game/game_data.h>
#include <game/server_client.h>
#include <game/map.h>

void loadAssets(void);

Window window;
Renderer renderer;

//Assets
fwTexture_t gameTexture;
fwTexture_t fontTexture;

Shader spriteShader;
Shader uiShader;

#define GAME_MUSICS_AMOUNT 1
streamedSound_t music[GAME_MUSICS_AMOUNT];

//Game Objects
server_t localServer;
client_t localClient;

map_t map;
mapTexture_t mapTexture;

int main() {
	if(!initPlatform()) {
		return 1;
	}
	if (!initAudio()) {
		return 2;
	}
	if (!initNetworking()) {
		return 3;
	}
	window = createWindow("WarsOfNations", 800, 600);
	renderer = createRenderer(window);
	loadAssets();
	loadTerrainTexture("data/terrain.png");

	mapGenerator_t generatorSettings;
	generatorSettings.w = 200;
	generatorSettings.h = 150;


	//Test Audio
	//playStreamedSound(&music[0]);
	updateSounds();

	//Setup Game
	localServer = initServer();
	localClient = initClient();
	map = createMap();
	mapTexture = createMapTexture();
	startServer(&localServer, GAME_DEFAULT_PORT);
	startClient(&localClient, "localhost", GAME_DEFAULT_PORT);
	generateMap(&map, &generatorSettings);
	//updateMapTexture(&renderer, &mapTexture, &map);

	vertex_t v[] = {
		{0.5f, 0.5f, (0.0f * UINT16_MAX), (0.0f * UINT16_MAX), 255, 0, 0, 255},
		{0.5f, -0.5f, (0.0f * UINT16_MAX), (1.0f * UINT16_MAX), 0, 255, 0, 255},
		{-0.5f, -0.5f, (1.0f * UINT16_MAX), (1.0f * UINT16_MAX), 255, 0, 255, 255},
		{-0.5f, 0.5f, (1.0f * UINT16_MAX), (0.0f * UINT16_MAX), 0, 255, 255, 255}
	};

	uint16_t i[] = {
		0, 1, 3, 1, 2, 3
	};

	Buffer buffer = rendererCreateBuffer(&renderer, sizeof(vertex_t) * 4, sizeof(uint16_t) * 6, true, true);

	while (isWindowOpen(window)) {
		windowPollEvents(window);

		updateServer(&localServer);

		rendererClear(&renderer, 0, 0, 255, 255);

		updateVertexBuffer(&renderer, &buffer, v, 4, 0);
		updateIndexBuffer16(&renderer, &buffer, i, 6, 0);
		renderGeometry(&renderer, &buffer, &uiShader, NULL, 6, 0);

		windowDisplay(window);
	}
	return 0;
}

void loadAssets(void) {
	textureLoadInfo_t textures[] = {
		{ "data/resources.png", TEXTURE_RESOURCES },
		{ "data/units.png", TEXTURE_UNITS }
	};

	gameTexture = loadTexture(&renderer, textures, 2, 256);
	fontTexture = loadSingleTexture(&renderer, "data/font.png");

	const char* defines[] = {
		"#define USE_VP_MATRIX\n"
	};

	spriteShader = createShader("data/shader1.glsl", "data/shader1.glsl", defines, 1);
	uiShader = createShader("data/shader1.glsl", "data/shader1.glsl", NULL, 0);

	music[0] = openStreamedSound("data/The_Mandolin_of_Azgravan.ogg");
}
