#include <platform/platform.h>
#include <stdio.h>
#include <framework/audio.h>

int main() {
	if(!initPlatform()) {
		return 1;
	}
	if (!initAudio()) {
		return 2;
	}
	Window window = createWindow("WarsOfNations", 800, 600);
	Renderer renderer = createRenderer(window);

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