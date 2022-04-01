#include <platform/platform.h>

#ifdef PLATFORM_SDLNET_IMPL
bool initNetworking() {
	return (SDLNet_Init() != -1);
}
Socket openServerSocket(uint16_t port) {
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, port);
	return SDLNet_TCP_Open(&ip);
}
Socket openClientSocket(const char* addr, uint16_t port) {
	IPaddress ip;
	SDLNet_ResolveHost(&ip, addr, port);
	return SDLNet_TCP_Open(&ip);
}
Socket acceptConnection(Socket* serverSock) {
	return SDLNet_TCP_Accept(*serverSock);
}
void closeSocket(Socket* sock) {
	SDLNet_TCP_Close(*sock);
}

int32_t socketSend(Socket* sock, void* data, uint32_t dataSize) {
	return SDLNet_TCP_Send(*sock, data, dataSize);
}
int32_t socketRecv(Socket* sock, void* data, uint32_t dataSize) {
	return SDLNet_TCP_Recv(*sock, data, dataSize);
}

SocketSelector createSocketSelector(uint32_t maxSockets) {
	return SDLNet_AllocSocketSet(maxSockets);
}
bool addSocket(SocketSelector* selector, Socket* sock) {
	SDLNet_GenericSocket gsock = (SDLNet_GenericSocket)*sock;
	return (SDLNet_AddSocket(*selector, gsock) > 0);
}
bool delSocket(SocketSelector* selector, Socket* sock) {
	SDLNet_GenericSocket gsock = (SDLNet_GenericSocket)*sock;
	return (SDLNet_DelSocket(*selector, gsock) != -1);
}
void checkSockets(SocketSelector* selector) {
	SDLNet_CheckSockets(*selector, 0);
}
bool isSocketReady(Socket* sock) {
	SDLNet_GenericSocket gsock = (SDLNet_GenericSocket)*sock;
	return gsock->ready;
}
#endif
