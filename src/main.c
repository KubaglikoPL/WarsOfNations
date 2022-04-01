#include <platform/platform.h>
#include <stdio.h>
#include <framework/audio.h>
#include <framework/texture.h>
#include <game/game_data.h>
#include <game/server_client.h>

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

	//Test Audio
	//playStreamedSound(&music[0]);
	updateSounds();

	//Setup Game
	localServer = initServer();
	localClient = initClient();
	startServer(&localServer, GAME_DEFAULT_PORT);
	startClient(&localClient, "localhost", GAME_DEFAULT_PORT);

	while (isWindowOpen(window)) {
		windowPollEvents(window);

		updateServer(&localServer);

		rendererClear(&renderer, 0, 0, 255, 255);

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

	const char* defines[] = {
		"#define USE_VP_MATRIX"
	};

	spriteShader = createShader("data/shader1.glsl", "data/shader1.glsl", defines, 1);
	uiShader = createShader("data/shader1.glsl", "data/shader1.glsl", NULL, 0);

	music[0] = openStreamedSound("data/The_Mandolin_of_Azgravan.ogg");
}
