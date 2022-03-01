#include "packet.h"
#include <string.h>

Packet createPacket(uint16_t id) {
	Packet p;
	p.header.magic = PACKET_HEADER_MAGIC;
	p.header.id = id;
	p.header.size = 0;
	p.header.type = 0;
	p.dataSize = 0;
	memset(&p.data, 0, UINT16_MAX);
	return p;
}

void clearPacket(Packet* packet) {
	if (packet) {
		packet->header.size = 0;
	}
}

void appendPacketData(Packet* packet, void* data, uint16_t dataSize) {
	if (packet) {
		memcpy(&packet->data[packet->header.size], data, dataSize);
		packet->header.size += dataSize;
	}
}

void sendPacket(Socket* socket, Packet* packet) {
	/*if (socket && packet) {
		if (socket->ptr) {
			socketSend(socket, packet->header, sizeof(PacketHeader));
			socketSend(socket, packet->header, packet->header.size);
		}
	}*/
}

bool receivePacket(Socket* socket, Packet* packet, uint32_t* recvPtr) {
	/*if (socket && packet && recvPtr) {
		if (socket->ptr) {
			uint32_t _recvPtr = *recvPtr;
			bool packetHeaderComplete = false;
			bool packetComplete = false;
			if (_recvPtr < sizeof(PacketHeader)) {
				uint32_t dataToGet = sizeof(PacketHeader) - _recvPtr;
				int32_t dataGotten = socketReceive(socket, (uint8_t*)&packet[_recvPtr], dataToGet);
				if (dataGotten == dataToGet) packetHeaderComplete = true;
				_recvPtr += (uint32_t)dataGotten;
			}
			if (packetHeaderComplete) {
				uint32_t dataToGet = (packet->header.size + sizeof(PacketHeader)) - _recvPtr;
				uint32_t packetDataOffset = (_recvPtr - sizeof(PacketHeader));
				if (dataToGet == 0) packetComplete = true;
				int32_t dataGotten = socketReceive(socket, (uint8_t*)&packet[_recvPtr], dataToGet);
				if (dataGotten == dataToGet) packetComplete = true;
				_recvPtr += (uint32_t)dataGotten;
			}

			if (packetComplete) {
				_recvPtr = 0;
			}
			*recvPtr = _recvPtr;
			return packetComplete;
		}
	}*/
	return false;
}
