#include "server_client.h"

gameClient createGameClient() {
	gameClient c;
	c.port = 0;
	c.socket = createSocket();
	c.sendPacket = createPacket(UNKOWN_CLIENT_ID);
	c.receivePacket = createPacket(UNKOWN_CLIENT_ID);
	c.connected = false;
	c.recvPtr = 0;
	return c;
}

void initGameClient(gameClient* client, uint16_t port, const char* addr, char* username) {
	if (openClintSocket(&client->socket, addr, port)) {
		client->connected = true;
		ClientConnectionInfoPacket connectionInfo;
		connectionInfo.protocolVersion = PROTOCOL_VERSION;
		SDL_memcpy(connectionInfo.username, username, USERNAME_MAX_LENGHT);
		sendPacketWithData(&client->socket, &client->sendPacket, &connectionInfo, sizeof(ClientConnectionInfoPacket), CLIENT_CONNECTION_INFO);
	}
}

void updateClient(gameClient* client) {
	if (receivePacket(&client->socket, &client->receivePacket, &client->recvPtr)) {
		if (client->receivePacket.header.id == SERVER_ID) {
			clientProcessEvent(client, client->receivePacket.header.type, client->receivePacket.data);
		}
	}
}

void clientProcessEvent(gameClient* client, uint16_t type, void* data) {
	if (type == SERVER_CONNECTION_INFO_RESPONSE) {
		ServerConnectionInfoResponsePacket* info = data;

		client->sendPacket.header.id = info->clientID;
	}
}
