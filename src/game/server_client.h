#pragma once

#include <network/packet.h>
#include "protocol.h"

#define MAX_CLIENT_CONNECTIONS 16

typedef struct {
	bool remote;
	Packet packet;
	Socket socket;

	bool connected;
	char username[USERNAME_MAX_LENGHT];
} clientConnection;

typedef struct {
	clientConnection connections[MAX_CLIENT_CONNECTIONS];
	uint32_t nextConnection;

	Socket serverSocket;
	uint16_t serverPort;
} gameServer;

gameServer createGameServer();
void initGameServer(gameServer *server, uint16_t port);
void updateServer(gameServer* server);

/*typedef struct {
	Socket socket;

} gameClient;*/