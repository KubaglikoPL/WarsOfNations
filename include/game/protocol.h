#pragma once

#include <stdint.h>
#include <stdbool.h>

#define SERVER_SIDE_PACKET 1000

typedef enum packetType {
	CONNECTION_INFO = 1,
	READY = 2,

	SELECT_CAPITAL_POSITION = 10,
	CREATE_CITY = 11,
	CREATE_UNIT = 12,
	CREATE_BUILDING = 13,
	UPGRADE_CITY = 14,
	MOVE_UNIT = 15,
	CHANGE_GOVERMENT = 16,
	BATTLE = 17,
	NUCLEAR_STRIKE = 18,

	CONNECTION_INFO_RESPONSE = (1 + SERVER_SIDE_PACKET),
	MAP_DATA = (2 + SERVER_SIDE_PACKET),
	MAP_DATA2 = (3 + SERVER_SIDE_PACKET),
	START_GAME = (4 + SERVER_SIDE_PACKET),
	UPDATE_PLAYER_DATA = (5 + SERVER_SIDE_PACKET),
	UPDATE_PLAYER_DATA2 = (6 + SERVER_SIDE_PACKET),

	SELECT_CAPITAL_POSITION_RESPONSE = (SELECT_CAPITAL_POSITION + SERVER_SIDE_PACKET),
	CREATE_CITY_RESPONSE = (CREATE_CITY + SERVER_SIDE_PACKET),
	CREATE_UNIT_RESPONSE = (CREATE_UNIT + SERVER_SIDE_PACKET),
	CREATE_BUILDING_RESPONSE = (CREATE_BUILDING + SERVER_SIDE_PACKET),
	UPGRADE_CITY_RESPONSE = (UPGRADE_CITY + SERVER_SIDE_PACKET),
	MOVE_UNIT_RESPONSE = (MOVE_UNIT + SERVER_SIDE_PACKET),
	CHANGE_GOVERMENT_RESPONSE = (CHANGE_GOVERMENT + SERVER_SIDE_PACKET),
	BATTLE_RESPONSE = (BATTLE + SERVER_SIDE_PACKET),
	NUCLEAR_STRIKE_RESPONSE = (NUCLEAR_STRIKE + SERVER_SIDE_PACKET),

	TURN = (100 + SERVER_SIDE_PACKET),
	ADVANCE_AGE = (101 + SERVER_SIDE_PACKET)
} packetType_t;

//Clientside
#pragma pack(push, 1)
typedef struct connectionInfo {
	float r, g, b;
	uint32_t nameSize;
} connectionInfo_t;

typedef struct selectCapitalPosition {
	uint16_t x, y;
	uint32_t cityName;
} selectCapitalPosition_t;

typedef struct createCity {
	uint16_t x, y;
	uint32_t cityName;
} createCity_t;

typedef struct createUnit {
	bool destroy;
	uint32_t cityID;
	uint32_t unitType;
} createUnit_t;

typedef struct createBuilding {
	bool destroy;
	uint32_t cityID;
	uint32_t buildingType;
} createBuilding_t;

/*typedef struct upgradeCity {
	uint32_t cityID;
	uint32_t upgradeType;
} upgradeCity_t;*/

typedef struct moveUnit {
	uint32_t unitID;
	uint16_t x, y;
} moveUnit_t;

typedef struct changeGoverment {
	uint32_t govermentBitset;
} changeGoverment_t;

//TODO Battle and Nuclear Strike
#pragma pack(pop)

//Serverside
#pragma pack(push, 1)
typedef struct connectionInfoResponse {
	uint32_t playerID;
} connectionInfoResponse_t;

typedef struct mapData {
	uint16_t w, h;
} mapData_t;

typedef struct mapData2 {
	uint32_t resourcesAmount;
} mapData2_t;

/*typedef struct startGame {

} startGame_t;*/

typedef struct updatePlayerData {
	uint32_t playerID;
	float r, g, b;
	uint32_t nameSize;
} updatePlayerData_t;

typedef struct updatePlayerData2 {
	uint32_t playerID;
	
	uint32_t production;
	uint32_t productionTotal;

	uint32_t money;
	uint32_t moneyTotal;

	uint32_t stability;
} updatePlayerData2_t;

typedef struct turn {
	uint32_t turnNumber;
} turn_t;

typedef struct advanceAge {
	uint32_t age;
} advanceAge_t;

typedef struct selectCapitalPositionResponse {
	bool valid;
	uint16_t x, y;
	uint32_t cityID;
	uint32_t playerID;
	uint32_t cityName;
} selectCapitalPositionResponse_t;

typedef struct createCityResponse {
	bool valid;
	uint16_t x, y;
	uint32_t cityID;
	uint32_t playerID;
	uint32_t cityName;
} createCityResponse_t;

typedef struct createUnitResponse {
	bool valid;
	bool destroy;
	uint32_t cityID;
	uint32_t playerID;
	uint32_t unitType;
	uint32_t unitID;
} createUnitResponse_t;

typedef struct createBuildingResponse {
	bool valid;
	bool destroy;
	uint32_t cityID;
	uint32_t buildingType;
} createBuildingResponse_t;

typedef struct moveUnitResponse {
	bool valid;
	uint32_t unitID;
	uint16_t x, y;
} moveUnitResponse_t;

typedef struct changeGovermentResponse {
	bool valid;
	uint32_t playerID;
	uint32_t govermentBitset;
} changeGovermentResponse_t;

//TODO Battle and Nuclear Strike
#pragma pack(pop)

#include <framework/packet.h>

void setupPacket(packet_t* packet, uint32_t type, void *data, uint32_t dataSize);
