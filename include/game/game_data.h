#pragma once

typedef enum {
	TEXTURE_RESOURCES,
	TEXTURE_UNITS,
	TEXTURE_CITIES,
	TEXTURE_BUILDINGS,
	TEXTURE_GOVERMENTS,
	TEXTURE_UI,

	TEXTURES_AMOUNT
} GameTextures;

typedef enum {
	PREHISTORY_AGE,
	ANCIENT_AGE,
	MIDDLE_AGE,
	RENAISSANCE_AGE,
	INDUSTRAL_AGE,
	MODERN_AGE,
	SPACE_AGE,

	AGES_AMOUNT
} Age;

typedef enum {
	WOOD,
	STONE,
	GOOD_EARTH,
	HORSE,
	GOLD,
	SALTPETER,
	COAL,
	OIL,
	URANIUM
} ResourceType;

typedef enum {
	HUNTER,

	CAVALERY,
	WARRIOR,
	ARCHER,
	SHIP,

	SPEARMAN,
	CROSSBOWMAN,
	HEAVY_CAVALERY,
	CATAPULT,

	RIFLEMAN,
	RENAISSANCE_INFANTRY,
	CANNON,
	FRIGATE,

	INFANTRY,
	TANK,
	STEAMBOAT,
	ARTILERY,
	AIRPLANE,
	ANTIAIR,

	MECHANIZED_INFANTRY,
	ROCKET_ARTILERY,
	AIRCRAFT_CARRIER,
	ATOMIC_BOMB,

	ICBM
} UnitType;

typedef enum {

} BuildingType;

typedef enum {
	TRIBAL_SYSTEM = (1 << 0),
	DESPOTISM = (1 << 1),
	OLIGARHY = (1 << 2),
	ATHENIAN_DEMOCRACY = (1 << 3),
	MONARCHY = (1 << 4),
	MERCHANT_REPUBLIC = (1 << 5),
	ABSOLUTE_MONARCHY = (1 << 6),
	IMPERIALISM = (1 << 7),
	REPUBLIC = (1 << 8),
	TOTALITARISM = (1 << 9),
	DEMOCRACY = (1 << 10),
	COMMUNISM = (1 << 11),
	FASCISM = (1 << 12),
	CAPITALISM = (1 << 13)
} GovermantType;

#include <stdint.h>

typedef struct {
	uint32_t tx_id;
	uint32_t tx_x;
	uint32_t tx_y;
} txInfo;

typedef struct {
	Age type;
	const char* name;
} ageInfo;

typedef struct {
	ResourceType type;
	txInfo tex;
	const char* name;
} resourceInfo;

typedef struct {
	UnitType type;
	uint32_t attack;
	uint32_t defence;
	const char* name;
} unitInfo;

/*typedef struct {

} buildingInfo;*/

typedef struct {
	GovermantType type;
	uint32_t requiredGoverments;
	const char* name;
} govermentInfo;


