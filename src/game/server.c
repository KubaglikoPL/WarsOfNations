#include "server_client.h"

gameServer createGameServer() {
	gameServer gs;
	gs.nextConnection = 0;
	gs.serverPort = 0;
	gs.serverSocket = createSocket();
	for (uint32_t i = 0; i < MAX_CLIENT_CONNECTIONS; i++) {
		gs.connections[i].connected = false;
		gs.connections[i].remote = false;
		gs.connections[i].packet = createPacket(SERVER_ID);
		gs.connections[i].socket = createSocket();
	}
	return gs;
}
void initGameServer(gameServer* server, uint16_t port) {
	server->serverPort = port;
	openServerSocket(&server->serverSocket, port);
}
void updateServer(gameServer* server) {

}
