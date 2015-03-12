#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdint.h>
#include <json/json.h>

#include <arena.h>
#include <player.h>
#include <round.h>

class Game {
private:
	Player* players;
	Round* rounds;


public:
	bool begin();
	bool end();
	bool settings();
};

#endif
