#include <platform/platform.h>
#include <malloc.h>
#ifdef PLATFORM_GL2_IMPL
#include "gl2.h"

#ifdef PLATFORM_GLFW_IMPL
#include <GLFW/glfw3.h>

void* glGetProc(const char* name) {
	return glfwGetProcAddress(name);
}
#endif

PFNGLGENTEXTURESPROC glGenTextures;
PFNGLBINDTEXTUREPROC glBindTexture;
PFNGLTEXIMAGE2DPROC glTexImage2D;
PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;
PFNGLDELETETEXTURESPROC glDeleteTexture;

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

PFNGLCLEARPROC glClear;
PFNGLCLEARCOLORPROC glClearColor;

PFNGLDRAWARRAYSPROC glDrawArrays;
PFNGLDRAWELEMENTSPROC glDrawElements;

typedef struct glRenderer {
	uint32_t activeTexture;
	uint32_t activeVBO;
	uint32_t activeEBO;
	uint32_t activeProgram;
} glRenderer_t;

Renderer createRenderer(Window window) {
	glRenderer_t* renderer = (glRenderer_t*)malloc(sizeof(glRenderer_t));
	renderer->activeTexture = 0;
	renderer->activeVBO = 0;
	renderer->activeEBO = 0;
	renderer->activeProgram = 0;

	glGenTextures = glGetProc("glGenTextures");
	glBindTexture = glGetProc("glBindTexture");
	glTexImage2D = glGetProc("glTexImage2D");
	glTexSubImage2D = glGetProc("glTexSubImage2D");
	glDeleteTexture = glGetProc("glDeleteTexture");

	glGenBuffers = glGetProc("glGenBuffers");
	glBufferData = glGetProc("glBufferData");
	glBufferSubData = glGetProc("glBufferSubData");
	glDeleteBuffers = glGetProc("glDeleteBuffers");
	glVertexAttribPointer = glGetProc("glVertexAttribPointer");
	glEnableVertexAttribArray = glGetProc("glEnableVertexAttribArray");

	glClear = glGetProc("glClear");
	glClearColor = glGetProc("glClearColor");
	glDrawArrays = glGetProc("glDrawArrays");
	glDrawElements = glGetProc("glDrawElements");

	return renderer;
}

Texture createTexture(Renderer renderer, uint32_t w, uint32_t h) {
	glRenderer_t* gl2_renderer = (glRenderer_t*)renderer;
	uint32_t texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	gl2_renderer->activeTexture = texture;
	return texture;
}

void destroyTexture(Texture texture) {
	glDeleteTexture(1, &texture);
}

void updateTexture(Renderer renderer, Texture texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data) {
	glRenderer_t* gl2_renderer = (glRenderer_t*)renderer;
	if(gl2_renderer->activeTexture != texture) glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	gl2_renderer->activeTexture = texture;
}

void rendererClear(Renderer renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
#endif
