#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <navigate.h>
#include <classify.h>
#include <settings.h>
#include <game.h>

#if defined(_WIN32) || defined(_WIN64)
#define clear_screen() system("cls")
#else
#define clear_screen() system("clear")
#endif

int main() {

	Game* game = Game::getGame();

	game->settings();

	char select = 0;

	do {
		std::cout << std::endl
			<< "1. Start \n"
			<< "2. Settings \n"
			<< "3. Quit \n"
			<< "?. ";
			
		std::cin >> select;

		switch(select) {
		case '1':
			clear_screen();
			game->begin();
			break;
		case '2':
			clear_screen();
			game->updateSettings();
			break;
		case '3':
			std::cout << "\nGood-Bye\n";
			break;
		}
	} while( select != '3');

	return 0;
}

