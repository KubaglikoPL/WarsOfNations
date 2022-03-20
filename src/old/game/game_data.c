#include "game_data.h"

ageInfo ages[] = {
	{ PREHISTORY_AGE, "Prehistory" },
	{ ANCIENT_AGE, "Ancient Age" },
	{ MIDDLE_AGE, "Middle Age" },
	{ RENAISSANCE_AGE, "Renaissance Age" },
	{ INDUSTRAL_AGE, "Industral Age" },
	{ MODERN_AGE, "Modern Age" },
	{ SPACE_AGE, "Space Age" }
};

resourceInfo resources[] = {
	{ WOOD, { TEXTURE_RESOURCES, 0, 0 }, "Wood" },
	{ STONE, { TEXTURE_RESOURCES, 16, 0 }, "Stone" },
	{ GOOD_EARTH, { TEXTURE_RESOURCES, 32, 0 }, "Good Earth" },
	{ HORSE, { TEXTURE_RESOURCES, 48, 0 }, "Horse" },
	{ GOLD, { TEXTURE_RESOURCES, 64, 0 }, "Gold" },
	{ SALTPETER, { TEXTURE_RESOURCES, 80, 0 }, "Saltpeter" },
	{ COAL, { TEXTURE_RESOURCES, 96, 0 }, "Coal" },
	{ OIL, { TEXTURE_RESOURCES, 112, 0 }, "Oil" },
	{ URANIUM, { TEXTURE_RESOURCES, 128, 0 }, "Uranium" },
};