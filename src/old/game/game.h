#pragma once

#include <stdint.h>

#define CITY_NAME_MAX 32
#define MAX_UNITS_PER_CITY 16

typedef struct {
	UnitType type;
} unit;

typedef struct {
	char name[CITY_NAME_MAX];
	unit units[MAX_UNITS_PER_CITY];
} city;

typedef struct {
	uint32_t citiesAmount;
	city* cities;


} gameState;

gameState createGameState();
void createCity();