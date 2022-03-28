#pragma once

#define TEXTURE_RESOURCES 1
#define TEXTURE_UNITS 2
#define TEXTURE_BUILDINGS 3

#include <framework/texture.h>

typedef struct {
	uint32_t ID;
	const char* name;

	uint32_t textureID;
	uint32_t tx_x, tx_y;
	texCoords_t tx_coords;

	uint32_t discoveryAge;
} resourceData;

typedef struct {
	uint32_t ID;
	const char* name;
} ageData;

typedef struct {
	uint32_t ID;
	const char* name;

	uint32_t textureID;
	uint32_t tx_x, tx_y;
	texCoords_t tx_coords;

	uint32_t productionBonus;
	uint32_t moneyBonus;
	uint32_t unitCapacityBonus;
	uint32_t cityPowerBonus;

	uint32_t requiredResource;
	bool spacePort;
} buildingData;

typedef struct {
	uint32_t ID;
	const char* name;

	uint32_t textureID;
	uint32_t tx_x, tx_y;
	texCoords_t tx_coords;

	uint32_t baseStability;
} govermentData;

typedef struct {
	uint32_t ID;
	const char* name;

	uint32_t textureID;
	uint32_t tx_x, tx_y;
	texCoords_t tx_coords;

	uint32_t age;

	uint32_t attack;
	uint32_t defence;
	bool airplane;
	bool antiAirplane;
	bool nuclear;
	bool water;
	uint32_t range;
} unitData;

#define RESOURCE_WOOD 1
#define RESOURCE_STONE 2
#define RESOURCE_EARTH 3
#define RESOURCE_HORSE 4
#define RESOURCE_GOLD 5
#define RESOURCE_SALTPETER 6
#define RESOURCE_COAL 7
#define RESOURCE_OIL 8
#define RESOURCE_URANIUM 9

#define AGE_PREHISTORY 1
#define AGE_ANCIENT 2
#define AGE_MEDIVAL 3
#define AGE_RENAISSANCE 4
#define AGE_INDUSTRAL 5
#define AGE_MODERN 6
#define AGE_SPACE 7

#define BUILDING_MINE 1
#define BUILDING_MARKET 2
#define BUILDING_WALL 3
#define BUILDING_FACTORY 4
#define BUILDING_MINT 5
#define BUILDING_BARRACKS 6
#define BUILDING_SPACE_PORT 7

static const resourceData resources[] = {
	{RESOURCE_WOOD, "Wood", TEXTURE_RESOURCES, 0, 0, {0,0,0,0}, AGE_PREHISTORY},
	{RESOURCE_STONE, "Stone", TEXTURE_RESOURCES, 16, 0, {0,0,0,0}, AGE_PREHISTORY},
	{RESOURCE_EARTH, "Good Earth", TEXTURE_RESOURCES, 32, 0, {0,0,0,0}, AGE_PREHISTORY},
	{RESOURCE_HORSE, "Horses", TEXTURE_RESOURCES, 48, 0, {0,0,0,0}, AGE_PREHISTORY},
	{RESOURCE_GOLD, "Gold", TEXTURE_RESOURCES, 64, 0, {0,0,0,0}, AGE_PREHISTORY},
	{RESOURCE_SALTPETER, "Saltpeter", TEXTURE_RESOURCES, 80, 0, {0,0,0,0}, AGE_RENAISSANCE},
	{RESOURCE_COAL, "Coal", TEXTURE_RESOURCES, 96, 0, {0,0,0,0}, AGE_INDUSTRAL},
	{RESOURCE_OIL, "Oil", TEXTURE_RESOURCES, 112, 0, {0,0,0,0}, AGE_INDUSTRAL},
	{RESOURCE_URANIUM, "Uranium", TEXTURE_RESOURCES, 128, 0, {0,0,0,0}, AGE_INDUSTRAL}
};

static const ageData ages[] = {
	{AGE_PREHISTORY, "Prehistory"},
	{AGE_ANCIENT, "Ancient Age"},
	{AGE_MEDIVAL, "Medival Age"},
	{AGE_RENAISSANCE, "Renaissance"},
	{AGE_INDUSTRAL, "Industrial Age"},
	{AGE_MODERN, "Modern Age"},
	{AGE_SPACE, "Space Age"}
};

static const buildingData buildings[] = {
	{BUILDING_MINE, "Mine", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 1, 0, 0, 0, 0, false},
	{BUILDING_MARKET, "Market", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 0, 1, 0, 0, 0, false},
	{BUILDING_WALL, "Wall", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 0, 0, 0, 4, 0, false},
	{BUILDING_FACTORY, "Factory", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 2, 0, 0, 0, RESOURCE_COAL, false},
	{BUILDING_MINT, "Mint", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 0, 2, 0, 0, RESOURCE_GOLD, false},
	{BUILDING_BARRACKS, "Barracks", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 0, 0, 1, 0, 0, false},
	{BUILDING_SPACE_PORT, "Space Port", TEXTURE_BUILDINGS, 0, 0, {0,0,0,0}, 0, 0, 0, 0, 0, true}
};
