#include "server_client.h"

gameServer createGameServer() {
	gameServer gs;
	gs.nextConnection = 0;
	gs.serverPort = 0;
	gs.serverSocket = createSocket();
	gs.serverPacket = createPacket(SERVER_ID);
	gs.gameStarted = false;
	gs.serverSetuped = false;
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		gs.connections[i].connected = false;
		gs.connections[i].remote = false;
		gs.connections[i].packet = createPacket(SERVER_ID);
		gs.connections[i].socket = createSocket();
		gs.connections[i].connectionInfoReceived = false;
		gs.connections[i].recvPtr = 0;
		gs.connections[i].playerReady = false;
	}
	return gs;
}
void initGameServer(gameServer* server, uint16_t port) {
	server->serverPort = port;
	openServerSocket(&server->serverSocket, port);
}

#include <ui/ui.h>

void updateServer(gameServer* server) {
	if (server->nextConnection != MAX_CLIENT_CONNECTIONS) {
		clientConnection* nextConnection = &server->connections[server->nextConnection];
		if (socketAcceptConnection(&server->serverSocket, &nextConnection->socket)) {
			nextConnection->connected = true;
			nextConnection->connectionInfoReceived = false;
			nextConnection->remote = true;
			server->nextConnection++;
		}
	}
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		clientConnection* connection = &server->connections[i];
		if (connection->connected && connection->remote) {
			if (receivePacket(&connection->socket, &connection->packet, &connection->recvPtr)) {
				serverProcessEvent(server, connection->packet.header.type, connection->packet.data, i, connection->packet.header.id);
			}
		}
	}
	if ((!server->gameStarted) && server->serverSetuped) {
		bool allPlayersReady = true;
		for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
			clientConnection* connection = &server->connections[i];
			if (connection->connected && connection->remote) {
				if (!connection->playerReady) allPlayersReady = false;
			}
		}
		if (allPlayersReady) {
			for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
				clientConnection* connection = &server->connections[i];
				sendPacketWithData(&connection->socket, &server->serverPacket, NULL, 0, SERVER_START_GAME);
				uiState = UI_STATE_GAME;
			}
		}
	}
}

#include <game/map_generator.h>

extern generatedMap map;
extern uint32_t mapWidth;
extern uint32_t mapHeight;
extern generatorSettings generator_settings;

void serverSetupGame(gameServer* server) {
	//If map not generated generate it
	if(map.width == 0) generateMap(&map, &generator_settings, mapWidth, mapHeight);
	//Prepare map data1
	uint32_t packetSize = (map.width * map.height * sizeof(mapTile)) + sizeof(ServerMapDataPacket);
	uint8_t* packetData = alloca(packetSize);
	ServerMapDataPacket* packetInfo = packetData;
	mapTile* tileData = &packetData[sizeof(ServerMapDataPacket)];
	packetInfo->mapWidth = map.width;
	packetInfo->mapHeight = map.height;
	SDL_memcpy(tileData, map.tileData, (packetSize - sizeof(ServerMapDataPacket)));

	//Send Map data to all clients
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		clientConnection* connection = &server->connections[i];
		if (connection->connectionInfoReceived) {
			sendPacketWithData(&connection->socket, &server->serverPacket, packetData, packetSize, SERVER_MAP_DATA);
		}
	}

	server->serverSetuped = true;
}

void serverProcessEvent(gameServer* server, uint16_t type, void* data, uint32_t connectionID, uint32_t packetID) {
	if ((type == CLIENT_CONNECTION_INFO) && (packetID == UNKOWN_CLIENT_ID)) {
		ClientConnectionInfoPacket* info = data;
		if (info->protocolVersion == PROTOCOL_VERSION) {
			server->connections[connectionID].connectionInfoReceived = true;
			SDL_memcpy(server->connections[connectionID].username, info->username, USERNAME_MAX_LENGHT);

			ServerConnectionInfoResponsePacket responce;
			responce.clientID = connectionID;
			responce.valid = true;

			sendPacketWithData(&server->connections[connectionID].socket, &server->serverPacket, &responce, sizeof(ServerConnectionInfoResponsePacket), SERVER_CONNECTION_INFO_RESPONSE);
		}
	}
	if (packetID != SERVER_ID) {
		if (type == CLIENT_READY) {
			server->connections[connectionID].playerReady = true;
		}
	}
}
