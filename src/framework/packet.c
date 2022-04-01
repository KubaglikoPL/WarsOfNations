#include <framework/packet.h>
#include <malloc.h>
#include <string.h>

packet_t createPacket() {
	packet_t p;
	//p.header.magic = PACKET_MAGIC;
	p.header.type = 0;
	p.header.dataSize = 0;
	p.dataCapacity = 0;
	p.dataSize = 0;
	p.data = NULL;
	p.recvPtr = 0;
	return p;
}

void resizePacket(packet_t* packet, uint32_t size) {
	if (packet) {
		packet->dataCapacity = size;
		packet->data = realloc(packet->data, size);
	}
}

void clearPacket(packet_t* packet) {
	if (packet) {
		packet->dataSize = 0;
		packet->recvPtr = 0;
	}
}

void appendDataToPacket(packet_t* packet, void* data, uint32_t size) {
	if (packet) {
		if ((packet->dataSize + size) > packet->dataCapacity) {
			resizePacket(packet, packet->dataSize + size);
		}
		memcpy(&packet->data[packet->dataSize], data, size);
		packet->dataSize += size;
	}
}

bool recvPacket(Socket* sock, packet_t* packet, bool *error) {
	if (sock && packet) {
		bool headerComplete = false;
		if (packet->recvPtr < sizeof(packetHeader_t)) {
			int32_t received = socketRecv(sock, &packet->header, sizeof(packetHeader_t) - packet->recvPtr);
			if (received <= 0) {
				if (error) error = true;
				return false;
			}
			packet->recvPtr += received;
			if (packet->recvPtr >= sizeof(packetHeader_t)) headerComplete = true;
			if (packet->header.dataSize > packet->dataCapacity) {
				resizePacket(packet, packet->header.dataSize);
			}
		}
		else headerComplete = true;

		if (headerComplete) {
			uint32_t recvPtrData = packet->recvPtr - sizeof(packetHeader_t);
			int32_t received = socketRecv(sock, &packet->data[recvPtrData], packet->header.dataSize - recvPtrData);
			if (received <= 0) {
				if (error) error = true;
				return false;
			}
			packet->recvPtr += received;
			recvPtrData = packet->recvPtr - sizeof(packetHeader_t);
			if (recvPtrData >= packet->header.dataSize) return true;
		}
	}

	return false;
}

bool sendPacket(Socket* sock, packet_t* packet) {
	if (sock && packet) {
		packet->header.dataSize = packet->dataSize;
		int32_t v1 = socketSend(sock, &packet->header, sizeof(packetHeader_t));
		int32_t v2 = socketSend(sock, packet->data, packet->dataSize);
		if ((v1 <= 0) || (v2 <= 0)) return false;
	}
	return true;
}
