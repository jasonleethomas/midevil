#include <json/json.h>
#include <fstream>
#include <settings.h>
#include <classify.h>
#include <character.h>
#include <wizard.h>
#include <warrior.h>
#include <iostream>
#include <string>

int main () {

	Json::Value playerSettings = Settings::getPlayerSettings(classify::First);

	std::string teamString = playerSettings["team"].asString();
	std::cout << "team: " << teamString << std::endl;

	teamString = classify::typeToString(classify::Warrior);
	std::cout << "team: " << teamString << std::endl;
	playerSettings["team"] = teamString;
	Settings::setPlayerSettings(classify::First, playerSettings);

	playerSettings = Settings::getPlayerSettings(classify::First);
	teamString = playerSettings["team"].asString();
	std::cout << "team: " << teamString << std::endl; 

	return 0;
}


