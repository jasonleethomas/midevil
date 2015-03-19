#include <game.h>
#include <iostream>

Game* Game::game = 0;

Game::Game() {};
Game::Game(Game const& copy) {};
Game& Game::operator=(Game const& copy) {};

Game* Game::getGame() {
	if(game == 0)
		game = new Game();

	return game;
}

bool Game::begin() {}

bool Game::end() {}

Game::~Game() {
	delete game;
}
