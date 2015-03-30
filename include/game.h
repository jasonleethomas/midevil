/*	Game.h
	Implements the Singleton Pattern
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <stdint.h>
#include <json/json.h>
#include <classify.h>
#include <player.h>
#include <arena.h>


class Game {
private:
	classify::Mode mode;
	Player* players[2];
	Arena* arena;

	Game(classify::Mode);
	Game(Game const& copy);
	Game& operator=(Game const& copy);

public:
	static Game* getGame(classify::Mode);

	void setTeams(classify::Type, classify::Type);
	void setArenaDimensions(navigate::Point);

	void begin();

	~Game();
};

#endif
