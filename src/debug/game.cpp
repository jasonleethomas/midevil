#include <game.h>
#include <iostream>

Game::Game() {};
Game::Game(Game const& copy) {};
Game& Game::operator=(Game const& copy) {};

Game* Game::getGame() {
	static Game game;

	return &game;
}

bool Game::begin() {}

bool Game::end() {}

Game::~Game() {}
