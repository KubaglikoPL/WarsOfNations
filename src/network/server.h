#pragma once

#include "packet.h"

#define MAX_SERVER_CONNECTIONS 16

struct ServerConnection {

};

struct Server {
	ServerConnection connections[MAX_SERVER_CONNECTIONS];
	uint8_t nextConnection = 0;
};