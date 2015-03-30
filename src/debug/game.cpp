#include <iostream>
#include <game.h>
#include <classify.h>
#include <player.h>
#include <arena.h>
#include <settings.h>

using namespace gameSettings;

Game::Game(classify::Mode mode) {
	this->mode = mode;
	setMode(this->mode);
};

Game* Game::getGame(classify::Mode mode) {
	static Game game(mode);

	return &game;
}

void Game::begin() {}


Game::~Game() {}
