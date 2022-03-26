#include <platform/platform.h>
#include <stdio.h>
#include <framework/audio.h>
#include <framework/texture.h>
#include <game/game_data.h>

void loadTextures(void);

Window window;
Renderer renderer;

fwTexture_t gameTexture;
fwTexture_t fontTexture;

int main() {
	if(!initPlatform()) {
		return 1;
	}
	if (!initAudio()) {
		return 2;
	}
	window = createWindow("WarsOfNations", 800, 600);
	renderer = createRenderer(window);
	loadTextures();

	//Test Audio
	streamedSound_t sound = openStreamedSound("data/The_Mandolin_of_Azgravan.ogg");
	playStreamedSound(&sound);
	updateSounds();

	while (isWindowOpen(window)) {
		windowPollEvents(window);

		rendererClear(renderer, 0, 0, 255, 255);

		windowDisplay(window);
	}
	return 0;
}

void loadTextures(void) {
	textureLoadInfo_t textures[] = {
		{ "data/resources.png", TEXTURE_RESOURCES },
		{ "data/units.png", TEXTURE_UNITS }
	};

	gameTexture = loadTexture(renderer, textures, 2, 256);
}
