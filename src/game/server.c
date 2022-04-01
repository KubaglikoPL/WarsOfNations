#include <game/server_client.h>

server_t initServer() {
	server_t s;
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		s.connections[i].playerID = INVALID_ID;
		s.connections[i].clientPacket = createPacket();
		s.connections[i].clientSocket = INVALID_SOCKET;
	}
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		s.players[i].connectionID = INVALID_ID;
		s.players[i].ready = false;
		//s.players[i].player = setupPlayer();
	}
	s.nextConnectionID = 0;
	s.nextPlayerID = 0;
	s.sendPacket = createPacket();
	s.serverSocket = INVALID_SOCKET;
	s.selector = createSocketSelector(MAX_CLIENT_CONNECTIONS);
	s.gameStarted = false;
	return s;
}

void startServer(server_t* server, uint16_t port) {
	server->serverSocket = openServerSocket(port);
}

void serverProcessEvent(server_t* server, packet_t* packet, uint32_t connectionID, uint32_t playerID);
void serverDisconnectPlayer(server_t* server, uint32_t connectionID, uint32_t playerID);

void updateServer(server_t* server) {
	if (SOCKET_IS_VALID(server->serverSocket)) {
		//Check for new connections
		Socket s = acceptConnection(&server->serverSocket);
		if (SOCKET_IS_VALID(s) && (server->nextConnectionID < MAX_CLIENT_CONNECTIONS)) {
			//New Connection
			server->connections[server->nextConnectionID].clientSocket = s;
			addSocket(&server->selector, &server->connections[server->nextConnectionID].clientSocket);
			server->nextConnectionID = MAX_CLIENT_CONNECTIONS;
			for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
				if (!SOCKET_IS_VALID(server->connections[i].clientSocket)) server->nextConnectionID = i;
			}
		}

		//Check if game can be started
		bool allPlayersReady = true;
		bool anyPlayerReady = false;
		for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
			if (server->players[i].connectionID != INVALID_ID) {
				if (server->players[i].ready) anyPlayerReady = true;
				else allPlayersReady = false;
			}
		}
		if (allPlayersReady && anyPlayerReady) {
			//Starts the game(TODO)
		}

		//Check for packets(TODO)
		checkSockets(&server->selector);
		for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
			if (SOCKET_IS_VALID(server->connections[i].clientSocket)) {
				if (isSocketReady(&server->connections->clientSocket)) {
					bool error = false;
					clientConnection_t* connection = &server->connections[i];
					bool packetReceived = recvPacket(&connection->clientSocket, &connection->clientPacket, &error);
					if (packetReceived) {
						serverProcessEvent(server, &connection->clientPacket, i, connection->playerID);
					}
					else if (error) {
						serverDisconnectPlayer(server, i, connection->playerID);
					}
				}
			}
		}

		//Update game(TODO)
	}
}

#include <game/protocol.h>

void serverProcessEvent(server_t* server, packet_t* packet, uint32_t connectionID, uint32_t playerID) {
	uint32_t type = packet->header.type;
	if (type == CONNECTION_INFO) {
		connectionInfo_t* info = packet->data;
		player_t p = setupPlayer();
		p.r = info->r;
		p.g = info->g;
		p.b = info->b;
		p.name = realloc(p.name, info->nameSize + 1);
		memset(p.name, 0, info->nameSize);
		memcpy(p.name, &packet->data[sizeof(connectionInfo_t)], info->nameSize);
		//TODO add Player
	}
	if (playerID != INVALID_ID) {

	}
	clearPacket(packet);
}

void serverDisconnectPlayer(server_t* server, uint32_t connectionID, uint32_t playerID) {
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		if (i == connectionID) {
			server->connections[i].playerID = INVALID_ID;
			closeSocket(&server->connections[i].clientSocket);
			delSocket(&server->selector, &server->connections[i].clientSocket);
		}
		if (i == playerID) {
			server->players[i].connectionID = INVALID_ID;
			server->players[i].ready = false;
		}
	}
}
