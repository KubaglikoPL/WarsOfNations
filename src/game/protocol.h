#pragma once

typedef enum {
	
} ServerPacketType;

typedef enum {
	CONNECTION_INFO
} ClientPacketType;

#define USERNAME_MAX_LENGHT 32

#pragma pack(push, 1)
typedef struct {
	char username[USERNAME_MAX_LENGHT];
} ClientConnectionInfoPacket;
#pragma pack(pop)