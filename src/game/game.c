#include <game/game.h>

player_t setupPlayer(void) {
	player_t p;
	p.r = 0.0f;
	p.g = 0.0f;
	p.b = 0.0f;
	p.name = NULL;
	p.selectedCapital = false;
	return p;
}