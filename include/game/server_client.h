#pragma once

#include <platform/platform.h>
#include <game/game.h>
#include <framework/packet.h>

#define INVALID_ID UINT32_MAX
#define MAX_CLIENT_CONNECTIONS 16
#define GAME_DEFAULT_PORT 32372

typedef struct clientConnection {
	Socket clientSocket;
	packet_t clientPacket;
	uint32_t playerID;
} clientConnection_t;

typedef struct serverPlayer {
	player_t player;
	uint32_t connectionID;
	bool ready;
} serverPlayer_t;

typedef struct server {
	SocketSelector selector;
	Socket serverSocket;
	packet_t sendPacket;
	clientConnection_t connections[MAX_CLIENT_CONNECTIONS];
	serverPlayer_t players[MAX_CLIENT_CONNECTIONS];
	uint32_t nextPlayerID;
	uint32_t nextConnectionID;
	bool gameStarted;
} server_t;

server_t initServer();
void startServer(server_t* server, uint16_t port);
void updateServer(server_t* server);

typedef struct client {
	Socket socket;
	SocketSelector selector;
	packet_t recvPacket;
	packet_t sendPacket;
} client_t;

#include <framework/packet.h>

client_t initClient();
bool startClient(client_t* client, const char* addr, uint16_t port);
