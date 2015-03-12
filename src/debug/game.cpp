#include <iostream>
#include <game.h>

Game::Game() {};
Game::Game(Game const& copy) {};
Game& Game::operator=(Game const& copy) {};

Game* Game::game = 0;

Game* Game::newGame() {
	if(game == 0)
		game = new Game;

	return game;
}

bool Game::begin() {}

bool Game::end() {}
