#include <network/server_client.h>

gameClient createGameClient() {
	gameClient c;
	c.port = 0;
	c.socket = createSocket();
	c.sendPacket = createPacket(UNKOWN_CLIENT_ID);
	c.receivePacket = createPacket(UNKOWN_CLIENT_ID);
	c.connected = false;
	c.recvPtr = 0;
	c.mapData1_received = false;
	c.mapData2_received = false;
	c.playerData_received = false;
	c.client_ready = false;
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

#include <game/map_generator.h>
#include <ui/game_ui.h>

extern generatedMap map;

void clientProcessEvent(gameClient* client, uint16_t type, void* data) {
	uint8_t* _data = data;
	if (type == SERVER_CONNECTION_INFO_RESPONSE) {
		ServerConnectionInfoResponsePacket* info = _data;
		client->sendPacket.header.id = info->clientID;
	}
	if (type == SERVER_MAP_DATA) {
		ServerMapDataPacket* info = _data;
		mapTile* tileData = &_data[sizeof(ServerMapDataPacket)];
		loadMap(&map, info->mapWidth, info->mapHeight, tileData);

		client->mapData1_received = true;
		client->client_ready = true; //Temporary

		sendPacketWithData(&client->socket, &client->sendPacket, NULL, 0, CLIENT_READY); //Temporary
	}
	if (type == SERVER_START_GAME) {
		uiState = UI_STATE_GAME;
	}
}
