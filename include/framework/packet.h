#pragma once

#include <platform/platform.h>

//#define PACKET_MAGIC 827215703

#pragma pack(push, 1)
typedef struct packetHeader {
	//uint32_t magic;
	uint32_t type;
	uint32_t dataSize;
} packetHeader_t;
#pragma pack(pop)

typedef struct packet {
	packetHeader_t header;

	uint32_t dataCapacity;
	uint32_t dataSize;
	uint8_t* data;

	uint32_t recvPtr;
} packet_t;

packet_t createPacket();

void resizePacket(packet_t* packet, uint32_t size);
void clearPacket(packet_t* packet);
void appendDataToPacket(packet_t *packet, void *data, uint32_t size);

bool recvPacket(Socket* sock, packet_t* packet, bool *error);
bool sendPacket(Socket* sock, packet_t* packet);
