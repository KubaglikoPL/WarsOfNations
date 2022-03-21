#pragma once

#include <SDL_net.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Socket {
	TCPsocket ptr;
	SDLNet_SocketSet set;
	IPaddress ip;
} Socket;

void initSocketApi();

Socket createSocket();
bool openServerSocket(Socket* socket, uint16_t port);
bool openClintSocket(Socket* socket, const char *addr, uint16_t port);
void closeSocket(Socket* socket);

bool socketAcceptConnection(Socket* socket, Socket* clientSocket);
int32_t socketReceive(Socket* socket, uint8_t* buffer, uint32_t bufferSize);
int32_t socketSend(Socket* socket, uint8_t* buffer, uint32_t dataSize);