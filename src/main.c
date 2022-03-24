#include <platform/platform.h>

int main() {
	if(!initPlatform()) {
		return 1;
	}
	if (!initAudio()) {
		return 2;
	}
	Window window = createWindow("WarsOfNations", 800, 600);
	Renderer renderer = createRenderer(window);

	while (isWindowOpen(window)) {
		windowPollEvents(window);

		rendererClear(renderer, 0, 0, 255, 255);

		windowDisplay(window);
	}
	return 0;
}