#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string>

#include <navigate.h>
#include <classify.h>
#include <game.h>
#include <arena.h>
#include <cell.h>
#include <object.h>
#include <character.h>
#include <wizard.h>
#include <warrior.h>
#include <obstacle.h>

#if defined(_WIN32) || defined(_WIN64)
#define clear_screen() system("cls")
#else
#define clear_screen() system("clear")
#endif

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

namespace error {
	bool flag = false;
	string message;
}

namespace gameio {
	enum Story {Introduction, SelectMode, SelectTeams, }
	int gameMode;
	int firstTeam;
	int secondTeam;
}

void cutscene();

int main() {

	cutscene();
	
	return 0;
}


void cutscene() {
	static int storypoint = 0;	
	std::string story;

	switch(storypoint) {
	case 0:
		story = \
		"In a time long, long ago, the Warriors of Rygon were locked \n\
		in deep battle against the Wizards of Zoruvia. \n\
		One day two mysterious figures, battle hardened and wise,\
		show up, claiming to have come from the future to end this \n\
		battle once and for all. The world awaited their decision \n\
		which sides were they on?";
		break;
	case 1:
		story = \;
		break;
	}

	std::cout << story;
	storypoint++;
}

void getTeams() {}

