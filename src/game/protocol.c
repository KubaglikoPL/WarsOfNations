#include <game/protocol.h>

void setupPacket(packet_t* packet, uint32_t type, void* data, uint32_t dataSize) {
	packet->header.type = type;
	clearPacket(packet);
	appendDataToPacket(packet, data, dataSize);
}
