#include <iostream>
#include <unistd.h>
#include <game.h>
#include <classify.h>
#include <player.h>
#include <arena.h>
#include <settings.h>

Game::Game() {
	this->mode = gameSettings::getMode();

	switch(this->mode) {
	case classify::Singleplayer:
		this->players[0] = new Player(classify::First);
		this->players[1] = new Player(classify::Computer);
		break;
	case classify::Multiplayer:
		this->players[0] = new Player(classify::First);
		this->players[1] = new Player(classify::Second);
		break;
	case classify::Simulation:
		this->players[0] = new Player(classify::Computer);
		this->players[1] = new Player(classify::Computer);
		break;
	}

	arena = Arena::getArena();
	arena->occupy();
};

Game* Game::getGame() {
	static Game game;

	return &game;
}

void Game::begin() {
	do {

		std::cout << arena->toString();
		arena->shuffle();

		sleep(1);

	} while(!arena->foundWinner());

	std::cout << arena->getWinner() << " wins!";
}

Game::~Game() {

	delete this->players[0];
	delete this->players[1];

}
