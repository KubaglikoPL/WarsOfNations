#include <game/server_client.h>
#include <game/protocol.h>

client_t initClient() {
	client_t c;
	c.recvPacket = createPacket();
	c.sendPacket = createPacket();
	c.selector = createSocketSelector(1);
	c.socket = INVALID_SOCKET;
	return c;
}

const char* userName = "Player1";

bool startClient(client_t* client, const char* addr, uint16_t port) {
	client->socket = openClientSocket(addr, port);
	if (client->socket) {
		connectionInfo_t data;
		data.r = 1.0f;
		data.g = 0.0f;
		data.b = 0.0f;
		data.nameSize = strlen(userName);
		setupPacket(&client->sendPacket, CONNECTION_INFO, &data, sizeof(connectionInfo_t));
		appendDataToPacket(&client->sendPacket, userName, data.nameSize);
		sendPacket(&client->socket, &client->sendPacket);
		return true;
	}
	else return false;
}
