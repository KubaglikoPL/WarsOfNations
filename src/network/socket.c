#include "socket.h"

void init_socket_api() {
	SDLNet_Init();
}

Socket createSocket() {
	Socket s;
	s.ptr = NULL;
	return s;
}

bool openServerSocket(Socket* socket, uint16_t port) {
	if (socket) {
		if (socket) closeSocket(socket);
		if (SDLNet_ResolveHost(&socket->ip, NULL, port) == -1) {
			return false;
		}
		socket->ptr = SDLNet_TCP_Open(&socket->ip);
		if (!socket->ptr) return false;
		else return true;
	}
	else return false;
}

bool openClintSocket(Socket* socket, const char* addr, uint16_t port) {
	if (socket) {
		if (socket) closeSocket(socket);
		if (SDLNet_ResolveHost(&socket->ip, addr, port) == -1) {
			return false;
		}
		socket->ptr = SDLNet_TCP_Open(&socket->ip);
		if (!socket->ptr) return false;
		else return true;
	}
	else return false;
}

void closeSocket(Socket* socket) {
	SDLNet_TCP_Close(socket->ptr);
	socket->ptr = NULL;
}

bool socketAcceptConnection(Socket* socket, Socket* clientSocket) {
	if (socket) {
		if (socket->ptr) {
			TCPsocket client = SDLNet_TCP_Accept(socket->ptr);
			if (client) {
				clientSocket->ptr = client;
				clientSocket->ip = *SDLNet_TCP_GetPeerAddress(clientSocket->ptr);
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

int32_t socketReceive(Socket* socket, uint8_t* buffer, uint32_t bufferSize) {
	if (socket) {
		if (socket->ptr) {
			return SDLNet_TCP_Recv(socket->ptr, buffer, bufferSize);
		}
	}
	return 0;
}

int32_t socketSend(Socket* socket, uint8_t* buffer, uint32_t dataSize) {
	if (socket) {
		if (socket->ptr) {
			return SDLNet_TCP_Send(socket->ptr, buffer, dataSize);
		}
	}
	return 0;
}
