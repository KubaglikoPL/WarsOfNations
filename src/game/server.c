#include "server_client.h"

gameServer createGameServer() {
	gameServer gs;
	gs.nextConnection = 0;
	gs.serverPort = 0;
	gs.serverSocket = createSocket();
	gs.serverPacket = createPacket(SERVER_ID);
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		gs.connections[i].connected = false;
		gs.connections[i].remote = false;
		gs.connections[i].packet = createPacket(SERVER_ID);
		gs.connections[i].socket = createSocket();
		gs.connections[i].connectionInfoReceived = false;
		gs.connections[i].recvPtr = 0;
	}
	return gs;
}
void initGameServer(gameServer* server, uint16_t port) {
	server->serverPort = port;
	openServerSocket(&server->serverSocket, port);
}
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
}
