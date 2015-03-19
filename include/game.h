/*	Game.h
	Implements the Singleton Pattern
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdint.h>
#include <json/json.h>

#include <player.h>
#include <arena.h>

class Game {
private:
	Player* players;
	Arena* arena;

	Game();
	Game(Game const& copy);
	Game& operator=(Game const& copy);

	static Game* game;
public:
	static Game* getGame();

	bool begin();
	bool end();
	bool settings();

	~Game();
};

#endif
