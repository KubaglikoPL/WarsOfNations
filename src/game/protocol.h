#pragma once

#include <stdbool.h>

#define PROTOCOL_VERSION 1

typedef enum {
	SERVER_CONNECTION_INFO_RESPONSE = 1
} ServerPacketType;

typedef enum {
	CLIENT_CONNECTION_INFO = 1
} ClientPacketType;

#define USERNAME_MAX_LENGHT 32

#pragma pack(push, 1)
typedef struct {
	uint16_t clientID;
	bool valid;
} ServerConnectionInfoResponsePacket;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t protocolVersion;
	char username[USERNAME_MAX_LENGHT];
} ClientConnectionInfoPacket;
#pragma pack(pop)
