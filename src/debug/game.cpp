#include <iostream>
#include <unistd.h>
#include <game.h>
#include <classify.h>
#include <player.h>
#include <arena.h>
#include <settings.h>

#if defined(_WIN32) || defined(_WIN64)
#define clear_screen() system("cls")
#else
#define clear_screen() system("clear")
#endif

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
	navigate::Point arenaDimensions;
	classify::Mode gameMode;
	classify::Type firstTeamType;
	classify::Type secondTeamType;

	int numCharacters = 0;
	int numObstacles = 0;
	int numPortalCells = 0;
	int numVacantCells = 0;
}

struct TeamCount {
	int grandCount;
	int masterCount;
	int lightCount;
	int darkCount;
} firstTeamCount, secondTeamCount;

TeamCount userCharacterCount(classify::User, classify::Type);
TeamCount randomCharacterCount(int numCharacters);

void gameModeSettings();
void playerTeamSettings();
void arenaDimensionsSettings();
void characterCountSettings();
void obstacleCountSettings();
void cellCountSettings();

int buyCharacter(classify::Level, classify::Type, int&);
void readFile(const char*);
std::string intToStars(int);
std::string attributesToString(classify::Level,
	classify::Type);

Game::Game() {}

Game* Game::getGame() {
	static Game game;

	return &game;
}

Game::~Game() {}

void Game::begin() {

	this->arena = Arena::getArena();
	this->arena->occupy();

	do {
		clear_screen();
		std::cout << arena->toString();
		arena->shuffle();

		usleep(250000);

	} while(!arena->foundWinner());

	std::cout << arena->getWinner() << " wins! \n";

	this->arena->empty();
}

void Game::settings() {	
	clear_screen();
	readFile(mode_story);
	gameModeSettings();

	classify::Mode gameMode = gameSettings::getMode();

	clear_screen();
	if(gameMode != classify::Simulation)
		readFile(team_story);
	playerTeamSettings();

	clear_screen();
	readFile(dimensions_story);
	arenaDimensionsSettings();

	clear_screen();
	if(gameMode != classify::Simulation)
		readFile(character_story);
	characterCountSettings();

	obstacleCountSettings();
}

void Game::updateSettings() {

	char select = 0;

	do {
		std::cout << std::endl
			<< "Settings \n"
			<< "1. Teams \n"
			<< "2. Dimensions \n"
			<< "3. Characters \n"
			<< "4. Return \n"
			<< "?. ";

		std::cin >> select;

		switch(select) {
		case '1':
			playerTeamSettings();
			characterCountSettings();
			break;
		case '2':
			arenaDimensionsSettings();
			characterCountSettings();
			break;
		case '3':
			characterCountSettings();
			break;
		}
	} while(select != '4');

	obstacleCountSettings();
}

void gameModeSettings() {
	char mode = 0;

	do {

		std::cout << std::endl
			<< "1. Singleplayer\n"
			<< "2. Multiplayer\n"
			<< "3. Simulation\n"
			<< "?: ";

		std::cin >> mode;
		std::cout << std::endl;

		if(!(mode == '1' || mode == '2' || mode == '3'))
			std::cout << "enter 1, 2, or 3";

	} while (!(mode == '1' || mode == '2' || mode == '3'));
	
	switch(mode) {
	case '1':
		options::gameMode = classify::Singleplayer;
		break;
	case '2':
		options::gameMode = classify::Multiplayer;
		break;
	case '3':
		options::gameMode = classify::Simulation;
		break;
	default:
		options::gameMode = classify::Simulation;
	}

	gameSettings::setMode(options::gameMode);
}

void playerTeamSettings() {

	classify::Mode gameMode = gameSettings::getMode();

	if(gameMode != classify::Simulation) {
		char team = 0;
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
			options::firstTeamType = classify::Warrior;
			options::secondTeamType = classify::Wizard;
			break;
		case '2':
			options::firstTeamType = classify::Wizard;
			options::secondTeamType = classify::Warrior;
			break;
		}
	}
	else {
		options::firstTeamType = classify::Warrior;
		options::secondTeamType = classify::Wizard;
	}

	playerSettings::setTeam(classify::First, 
		options::firstTeamType);
	playerSettings::setTeam(classify::Second,
		options::secondTeamType);
	playerSettings::setTeam(classify::Computer, 
		options::secondTeamType);
}

void arenaDimensionsSettings() {

	int xdim = 0;
	int ydim = 0;
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

	options::arenaDimensions.x = xdim;
	options::arenaDimensions.y = ydim;

	arenaSettings::setDimensions(options::arenaDimensions);
}

void characterCountSettings() {

	navigate::Point dimensions = arenaSettings::getDimensions();

	int area = dimensions.x * dimensions.y;

	options::numCharacters = (int) (area / 3);
	int minCharacterCost = 
		characterSettings::getCharacterCost(classify::Light,
			options::firstTeamType);

	int playerCoin = options::numCharacters * minCharacterCost;

	playerSettings::setCoin(classify::First, playerCoin);
	playerSettings::setCoin(classify::Second, playerCoin);

	switch(options::gameMode) {
	case classify::Singleplayer:
		firstTeamCount = userCharacterCount(classify::First, 
			options::firstTeamType);
		secondTeamCount = randomCharacterCount(options::numCharacters);
		break;
	case classify::Multiplayer:
		firstTeamCount = userCharacterCount(classify::First, 
			options::firstTeamType);
		secondTeamCount = userCharacterCount(classify::Second,
			options::secondTeamType);
		break;
	case classify::Simulation:
		firstTeamCount = randomCharacterCount(options::numCharacters);
		secondTeamCount = randomCharacterCount(options::numCharacters);
		break;
	}

	characterSettings::setCharacterCount(classify::Grand, 
		options::firstTeamType, firstTeamCount.grandCount);
	characterSettings::setCharacterCount(classify::Master, 		
		options::firstTeamType, firstTeamCount.masterCount);
	characterSettings::setCharacterCount(classify::Dark, 
		options::firstTeamType, firstTeamCount.lightCount);
	characterSettings::setCharacterCount(classify::Light, 
		options::firstTeamType, firstTeamCount.darkCount);

	characterSettings::setCharacterCount(classify::Grand, 
		options::secondTeamType, secondTeamCount.grandCount);
	characterSettings::setCharacterCount(classify::Master, 
		options::secondTeamType, secondTeamCount.masterCount);
	characterSettings::setCharacterCount(classify::Dark, 
		options::secondTeamType, secondTeamCount.lightCount);
	characterSettings::setCharacterCount(classify::Light, 
		options::secondTeamType, secondTeamCount.darkCount);
}

void obstacleCountSettings() {
	options::numObstacles = (int) ((options::arenaDimensions.x 
		* options::arenaDimensions.y) - options::numCharacters) / 3;
	
	obstacleSettings::setObstacleCount(options::numObstacles);	
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

TeamCount userCharacterCount(classify::User user, classify::Type team) {

	std::string playerString = classify::userToString(user) 
		+ " player";

	int coin = playerSettings::getCoin(user);

	std::cout << std::endl
		<< playerString << " +" << coin 
		<< std::endl;

	std::cout << std::endl
		<< attributesToString(classify::Grand, team)
		<< attributesToString(classify::Master, team)
		<< attributesToString(classify::Light, team)
		<< attributesToString(classify::Dark, team);

	TeamCount teamCount;
	
	std::cout << "Enter number of fighters from each class \n";

	teamCount.grandCount = buyCharacter(classify::Grand, 
		team, coin);
	teamCount.masterCount = buyCharacter(classify::Master, 
		team, coin);
	teamCount.lightCount = buyCharacter(classify::Light, 
		team, coin);
	teamCount.darkCount = buyCharacter(classify::Dark, 
		team, coin);

	playerSettings::setCoin(user, coin);

	return teamCount;
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
		else {
			std::cout << "not enough coin \n"
				<< "coin left: " << coin << "rb \n";
		}
	} while(!completedBuy);

	return characterCount;
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

std::string intToStars(int times) {
	std::string stars;
	for(int i = 0; i < times; i++)
		stars += "*";
	
	return stars;
}

TeamCount randomCharacterCount(int numCharacters) {
	TeamCount characterCount = {0,0,0,0};

	for(int i = 0; i < numCharacters; i++) {
		int randSeed = rand() % 10;
		if(randSeed < 1)
			characterCount.grandCount += 1;
		else if(randSeed < 3)
			characterCount.masterCount += 1;
		else if(randSeed < 6)
			characterCount.lightCount += 1;
		else if(randSeed <= 9)
			characterCount.darkCount += 1;
	}

	return characterCount;
}
