#pragma once

#include <stdbool.h>

#define PROTOCOL_VERSION 1

//1-9 connection
//10-19 game initialization
//20-99 gameplay

typedef enum {
	SERVER_CONNECTION_INFO_RESPONSE = 1, //DONE

	SERVER_MAP_DATA = 10, //DONE
	SERVER_MAP_DATA2 = 11, //TO IMPLEMENT
	SERVER_START_GAME = 12, //DONE
	SERVER_UPDATE_PLAYER_DATA = 13, //TO IMPLEMENT
	
	SERVER_SELECT_CAPITAL_RESPONSE = 20, //TO IMPLEMENT
	SERVER_CREATE_CITY_RESPONSE = 21, //TO IMPLEMENT
	SERVER_CREATE_UNIT_RESPONSE = 22, //TO IMPLEMENT
	SERVER_CREATE_BUILDING_RESPONSE = 23, //TO IMPLEMENT
	SERVER_MOVE_UNIT_RESPONSE = 24, //TO IMPLEMENT
	SERVER_CHANGE_GOVERMENT_RESPONSE = 25, //TO IMPLEMENT
	SERVER_BATTLE_RESPONSE = 26, //TO IMPLEMENT
	SERVER_UPGRADE_CITY_RESPONSE = 27, //TO IMPLEMENT

	SERVER_ADVANCE_AGE = 90, //TO IMPLEMENT
	SERVER_TURN = 91 //TO IMPLEMENT
} ServerPacketType;

typedef enum {
	CLIENT_CONNECTION_INFO = 1, //DONE

	CLIENT_READY = 10, //DONE

	CLIENT_SELECT_CAPITAL_POSITION = 20, //TO IMPLEMENT
	CLIENT_CREATE_CITY = 21, //TO IMPLEMENT
	CLIENT_CREATE_UNIT = 22, //TO IMPLEMENT
	CLIENT_CREATE_BUILDING = 23, //TO IMPLEMENT
	CLIENT_MOVE_UNIT = 24, //TO IMPLEMENT
	CLIENT_CHANGE_GOVERMENT = 25, //TO IMPLEMENT
	CLIENT_BATTLE = 26, //TO IMPLEMENT
	CLIENT_UPGRADE_CITY = 27 //TO IMPLEMENT
} ClientPacketType;

#define USERNAME_MAX_LENGHT 32

#pragma pack(push, 1)
typedef struct {
	uint16_t clientID;
	bool valid;
} ServerConnectionInfoResponsePacket;

typedef struct {
	uint16_t mapWidth;
	uint16_t mapHeight;

} ServerMapDataPacket;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t protocolVersion;
	char username[USERNAME_MAX_LENGHT];
} ClientConnectionInfoPacket;
#pragma pack(pop)
