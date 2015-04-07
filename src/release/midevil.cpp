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

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

const char* mode_story = "./res/story/mode";
const char* team_story = "./res/story/team";
const char* character_story = "./res/story/characters";
const char* dimensions_story = "./res/story/dimensions";
const char* begin_story = "./res/story/begin";

namespace error {
	bool flag = false;
	string message;
}

namespace options {
	navigate::Point dimensions;
	classify::Mode mode;
	classify::Type team;
	
	int numCharacters = 0;
}

struct characterCount {
	int grandCount;
	int masterCount;
	int lightCount;
	int darkCount;
};

void selectTeam(classify::User);
int buyCharacter(classify::Level, classify::Type, int&);
void readFile(const char*);
std::string intToStars(int);
std::string attributesToString(classify::Level,
	classify::Type);

int main() {
	char mode = 0;
	char team = 0;
	int xdim = 0;
	int ydim = 0;

	clear_screen();
	
	readFile(mode_story);

	do {

		std::cout << std::endl
			<< "1. Singleplayer \n"
			<< "2. Multiplayer 	\n"
			<< "?: ";

		std::cin >> mode;
		std::cout << std::endl;

		if(!(mode == '1' || mode == '2'))
			std::cout << "enter 1 or 2";

	} while (!(mode == '1' || mode == '2'));
	
	switch(mode) {
	case '1':
		options::mode = classify::Singleplayer;
		break;
	case '2':
		options::mode = classify::Multiplayer;
		break;
	}

	gameSettings::setMode(options::mode);
	
	readFile(team_story);
	
	do {

		std::cout << std::endl
			<< "1. Warriors \n"
			<< "2. Wizards	\n"
			<< "?.";

		std::cin >> team;
		std::cout << std::endl;

		if(!(team == '1' || team == '2'))
			std::cout << "enter 1 or 2";

	} while(!(team == '1' || team == '2'));

	switch(team) {
	case '1':
		options::team = classify::Warrior;
		break;
	case '2':
		options::team = classify::Wizard;
		break;
	}

	playerSettings::setTeam(classify::First, options::team);
	
	readFile(dimensions_story);

	int area = 0;

	do {
		
		std::cout << std::endl;
		std::cout << "Width?  ";
		std::cin >> xdim;

		std::cout << "Length? ";
		std::cin >> ydim;
		std::cout << std::endl;

		area = xdim * ydim;

		if(area > 401)
			std::cout << "too large, the villages will be massacred \n";
		if(area < 24)
			std::cout << "too small, your fighters need space.";

	} while(area > 401 || area < 24);

	options::dimensions.x = xdim;
	options::dimensions.y = ydim;

	arenaSettings::setDimensions(options::dimensions);

/* I'm gonna set the coin for each player as 1/3 of the area
	times the cost of the expensive character. this would limit the 
	maximum numbers of characters to all 
*/

	options::numCharacters = (int) (area / 3);
	int characterCost = 
		characterSettings::getCharacterCost(classify::Light,
			options::team);

	int playerCoin = options::numCharacters * characterCost;

	readFile(character_story);
	
	playerSettings::setCoin(classify::First, playerCoin);

	selectTeam(classify::First);

	if(options::mode == classify::Multiplayer) {

		switch(options::team)	{
		case classify::Warrior:	
			playerSettings::setTeam(classify::Second, classify::Wizard);
			break;
		case classify::Wizard:
			playerSettings::setTeam(classify::Second, classify::Warrior);
			break;
		}

		playerSettings::setCoin(classify::Second, playerCoin);

		selectTeam(classify::Second);
	}

	return 0;
}

std::string attributesToString(classify::Level level,
	classify::Type type) {

	using namespace characterSettings;

	std::string attributes;

	attributes += classify::levelToString(level) + " ";
	attributes += classify::typeToString(type) 
		+ "\n";
	attributes += "cost   "
		+ intToString(getCharacterCost(level, type))
		+ "rb \n";
	attributes += "damage " 
		+ intToStars(getCharacterDamage(level, type))
		+ "\n";
	attributes += "health " 
		+ intToStars(getCharacterHealth(level, type))
		+ "\n";
	attributes += "range  " 
		+ intToStars(getCharacterRange(level, type))
		+ "\n";
	attributes += "speed  " 
		+ intToStars(getCharacterSpeed(level, type))
		+ "\n";
		
	attributes += "\n";

	return attributes;
}

void selectTeam(classify::User user) {

	classify::Type team = playerSettings::getTeam(user);

	std::string playerString = classify::userToString(user) + 
	" player";

	int coin = playerSettings::getCoin(user);

	std::cout << std::endl
		<< playerString << " +" << coin 
		<< std::endl;

	std::cout << std::endl
		<< attributesToString(classify::Grand, team)
		<< attributesToString(classify::Master, team)
		<< attributesToString(classify::Light, team)
		<< attributesToString(classify::Dark, team);

	characterCount teamCount;
	
	std::cout << "Enter number of fighters from each class \n";

	teamCount.grandCount = buyCharacter(classify::Grand, 
		team, coin);
	teamCount.masterCount = buyCharacter(classify::Master, 
		team, coin);
	teamCount.grandCount = buyCharacter(classify::Light, 
		team, coin);
	teamCount.grandCount = buyCharacter(classify::Dark, 
		team, coin);

	characterSettings::setCharacterCount(classify::Grand, team,
		teamCount.grandCount);
	characterSettings::setCharacterCount(classify::Master, team,
		teamCount.masterCount);
	characterSettings::setCharacterCount(classify::Dark, team,
		teamCount.lightCount);
	characterSettings::setCharacterCount(classify::Light, team,
		teamCount.darkCount);
	
}

void readFile(const char* filename) {
	std::ifstream fin(filename, std::ios_base::out);
	if(fin.is_open())	{
		char ch;
		while(fin.get(ch))
			std::cout << ch;
	}

	fin.close();
} 

std::string intToStars(int times) {
	std::string stars;
	for(int i = 0; i < times; i++)
		stars += "*";
	
	return stars;
}

int buyCharacter(classify::Level level, classify::Type type, 
	int& coin) {
	
	std::string levelString = classify::levelToString(level);
	std::string typeString = classify::typeToString(type);
	std::string characterString = levelString + " " + typeString;

	int characterCost 
		= characterSettings::getCharacterCost(level, type);

	int characterCount = 0;
	int totalCost = 0;
	bool completedBuy = false;

	do {	

		std::cout << std::endl
			<< characterString << " [" << characterCost << "rb]x :" ;
		std::cin >> characterCount;

		totalCost = characterCount * characterCost;

		if(totalCost <= coin) {
		
			coin -= totalCost;

			std::cout << "[coins rattle] -" << totalCost << "rb"
				<< std::endl;

			std::cout << "coin left: " << coin << "rb \n";

			completedBuy = true;
		}		
		else 
			std::cout << "not enough coin \n";

	} while(!completedBuy);

	return characterCount;
}
