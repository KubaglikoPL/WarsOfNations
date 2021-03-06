#pragma once

#include <stdint.h>
#include <stdbool.h>

#if 0

#else
	#include "platform_glfw.h"
	#include "platform_miniaudio.h"
	#include "platform_gl2.h"
	#include "platform_sdlNet.h"
	#define PLATFORM_GLFW_IMPL	
	#define PLATFORM_MINIAUDIO_IMPL
	#define PLATFORM_GL2_IMPL
	#define PLATFORM_SDLNET_IMPL
#endif
#ifdef _WIN32
	
#else

#endif

//Common
#define MAX_ERROR_LENGTH 1024

const char* getLastError(void);
void setLastError(const char* e);
bool thereIsLastError(void);

//Window, Events and stuff
bool initPlatform(void);

Window createWindow(const char* title, uint32_t w, uint32_t h);
bool isWindowOpen(Window window);
void windowDisplay(Window window);
void windowPollEvents(Window window);
//Rendering
#pragma pack(push, 1)
typedef struct vertex {
	float x, y;
	uint16_t u, v;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} vertex_t;
#pragma pack(pop)

Renderer createRenderer(Window window);

Texture createTexture(Renderer *renderer, uint32_t w, uint32_t h);
void destroyTexture(Texture *texture);
void updateTexture(Renderer *renderer, Texture *texture, uint32_t x, uint32_t y, uint32_t w, uint32_t h, void* data);

void rendererClear(Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
Buffer rendererCreateBuffer(Renderer *renderer, uint32_t VBO_Size, uint32_t EBO_Size, bool shortIndicies, bool dynamicBuffer);
void updateVertexBuffer(Renderer* renderer, Buffer* buffer, vertex_t* v, uint32_t vNum, uint32_t off);
void updateIndexBuffer(Renderer* renderer, Buffer* buffer, uint32_t* i, uint32_t iNum, uint32_t off);
void updateIndexBuffer16(Renderer* renderer, Buffer* buffer, uint16_t* i, uint32_t iNum, uint32_t off);

Shader createShader(const char* vertexShader, const char* fragmentShader, const char** defines, uint32_t numDefines);

void renderGeometry(Renderer* renderer, Buffer* buffer, Shader* shader, Texture* texture, uint32_t num, uint32_t off);

//Audio
#define CHANNELS_AMOUNT 2

#define MAX_AUDIO_SOURCES 32

typedef struct audioSource {
	bool active;
	void* userData;
	uint32_t type;
	uint32_t(*getSamples)(void*, float*, uint32_t);
} audioSource_t;

bool initAudio();
void updateAudio(audioSource_t* sources);
//Networking
bool initNetworking(void);
Socket openServerSocket(uint16_t port);
Socket openClientSocket(const char *addr, uint16_t port);
Socket acceptConnection(Socket* serverSock);
void closeSocket(Socket* sock);

int32_t socketSend(Socket* sock, void* data, uint32_t dataSize);
int32_t socketRecv(Socket* sock, void* data, uint32_t dataSize);

SocketSelector createSocketSelector(uint32_t maxSockets);
bool addSocket(SocketSelector* selector, Socket* sock);
bool delSocket(SocketSelector* selector, Socket* sock);
void checkSockets(SocketSelector* selector);
bool isSocketReady(Socket* sock);