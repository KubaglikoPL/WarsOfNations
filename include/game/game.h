#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MAX_BUILDINGS_IN_CITY 4
#define MAX_UNITS_IN_CITY 16

typedef struct player {
	const char* name;
	float r, g, b;
	bool selectedCapital;
} player_t;

typedef struct city {
	const char* name;
	uint32_t ID;

	uint16_t x, y;
	uint32_t originalOwner;
	uint32_t currentOwner;
	bool capital;

	uint32_t buildings[MAX_BUILDINGS_IN_CITY];
	uint32_t units[MAX_UNITS_IN_CITY];
	uint32_t maxBuildings;
	uint32_t production;
	uint32_t money;
	uint32_t maxUnits;
} city_t;

player_t setupPlayer(void);
