#pragma once

#include <network/packet.h>
#include "protocol.h"

#define MAX_CLIENT_CONNECTIONS 16

typedef struct {
	bool remote;
	Packet packet;
	Socket socket;
	uint32_t recvPtr;

	bool connected;
	bool connectionInfoReceived;
	char username[USERNAME_MAX_LENGHT];
} clientConnection;

typedef struct {
	clientConnection connections[MAX_CLIENT_CONNECTIONS];
	uint32_t nextConnection;

	Packet serverPacket;
	Socket serverSocket;
	uint16_t serverPort;
} gameServer;

gameServer createGameServer();
void initGameServer(gameServer *server, uint16_t port);
void updateServer(gameServer* server);
void serverProcessEvent(gameServer* server, uint16_t type, void* data, uint32_t connectionID, uint32_t packetID);

typedef struct {
	Socket socket;
	Packet sendPacket;
	Packet receivePacket;
	uint32_t recvPtr;

	uint16_t port;
	bool connected;
} gameClient;

gameClient createGameClient();
void initGameClient(gameClient* client, uint16_t port, const char* addr, char* username);
void updateClient(gameClient* client);
void clientProcessEvent(gameClient* client, uint16_t type, void* data);
