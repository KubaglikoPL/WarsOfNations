/*#include <platform/platform.h>

#ifdef PLATFORM_WINSOCK_IMPL
#include <winsock2.h>
#include <ws2def.h>

bool initNetworking(void) {
	WSADATA d;
	return !WSAStartup(MAKEWORD(2, 2), &d);
}

Socket openServerSocket(uint16_t port) {
	Socket s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_IS_VALID(s)) {
		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = inet_addr("127.0.0.1");
		service.sin_port = htons(port);
		bind(s, (SOCKADDR*)&service, sizeof(service));
		listen(s, SOMAXCONN);
	}
	return s;
}

Socket openClientSocket(const char* addr, uint16_t port) {
	Socket s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_IS_VALID(s)) {
		uint32_t host = 0;
		host = inet_addr(addr);
		if (host == INADDR_NONE) {
			struct hostent* hp;
			hp = gethostbyname(addr);
			if (hp) {
				memcpy(&host, hp->h_addr, hp->h_length);
			}
		}

		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = host;
		service.sin_port = htons(port);
		bind(s, (SOCKADDR*)&service, sizeof(service));
		connect()
	}
	return s;
}

Socket acceptConnection(Socket* serverSock) {
	return accept(*serverSock, NULL, NULL);
}

void closeSocket(Socket* sock) {
	closesocket(*sock);
}

#endif*/
