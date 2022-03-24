#include <platform/platform.h>
#ifdef PLATFORM_GLFW_IMPL

bool initPlatform(void) {
	return glfwInit();
}

Window createWindow(const char* title, uint32_t w, uint32_t h) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	Window window = glfwCreateWindow(w, h, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	return window;
}
bool isWindowOpen(Window window) {
	return (!glfwWindowShouldClose(window));
}
void windowDisplay(Window window) {
	glfwSwapBuffers(window);
}
void windowPollEvents(Window window) {
	glfwPollEvents();
}
#endif
