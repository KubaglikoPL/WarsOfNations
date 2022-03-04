#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "socket.h"

#define PACKET_HEADER_MAGIC 1347309399 //ASCII 'WONP'
#define SERVER_ID UINT16_MAX
#define UNKOWN_CLIENT_ID (UINT16_MAX-1)

#pragma pack(push, 1)
typedef struct PacketHeader {
	uint32_t magic;
	uint32_t size;
	uint16_t type;
	uint16_t id;
} PacketHeader;
#pragma pack(pop)

typedef struct Packet {
	PacketHeader header;
	uint32_t dataSize;
	uint8_t *data;
} Packet;

Packet createPacket(uint16_t id);
void clearPacket(Packet *packet);
void resizePacket(Packet* packet, uint32_t size);
void appendPacketData(Packet* packet, void* data, uint32_t dataSize); //DON'T AUTO RESIZE THE PACKET

void sendPacket(Socket* socket, Packet* packet);
bool receivePacket(Socket* socket, Packet* packet, uint32_t* recvPtr);

void sendPacketWithData(Socket* socket, Packet* packet, void* data, uint32_t dataSize, uint16_t type); //Helper function