/*	Game.h
	Implements the Singleton Pattern
*/

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
	static Game* game;

	Player* players;
	Round* rounds;

	Game();
	Game(Game const& copy);
	Game& operator=(Game const& copy);

public:
	static Game* newGame();

	bool begin();
	bool end();
	bool settings();
};

#endif
