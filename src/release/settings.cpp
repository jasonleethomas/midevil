#include <settings.h>
#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <classify.h>
#include <game.h>
#include <player.h>
#include <arena.h>
#include <object.h>
#include <obstacle.h>
#include <character.h>

const char* Settings::filename = "./conf/settings.json";
Settings* Settings::handle = 0;

Settings::Settings() {
	this->in.open(filename);
	if(this->in.is_open()) 
		this->in >> this->settings;

	this->in.close();
}

Settings* Settings::getHandle() {
	if(handle == 0)
		handle = new Settings();

	return handle;
}

Json::Value Settings::getSettings(std::string thisclass) const {
	return this->settings[thisclass];
}

Json::Value Settings::getGameSettings() {

}

Json::Value Settings::getArenaSettings(Point dimensions) {

}

Json::Value Settings::getCharacterSettings(classify::Level level, 
	classify::Type type) {

	std::string levelString;
	std::string typeString;

	switch(level) {
	case classify::Grand:
		levelString = "grand";	
		break;
	case classify::Master:
		levelString = "master"; 
		break;
	case classify::Light:
		levelString = "light";
		break;
	case classify::Dark:
		levelString = "dark";	
		break;
	}

	switch(type) {
	case classify::Warrior:
		typeString = "warrior";	
		break;
	case classify::Wizard:
		typeString = "wizard";
		break;
	}			
	
	Settings* settings = getHandle();
	Json::Value characterSettings 
		= settings->getSettings("character");	

	return characterSettings[typeString][levelString];
}

namespace gameSettings {}

namespace playerSettings {
	Type getTeam() {}
	int getHP() {}
}

namespace arenaSettings {
	int getXDim() {}
	int getYDim() {}
}

namespace objectSettings {
	int getCount() {}
}

namespace obstacleSettings {
	int getCount() {}
}

namespace characterSettings {
	using classify::Level;
	using classify::Type;

	int getCharacterHealth(classify::Level level, classify::Type type) {
		Json::Value characterSettings = Settings::getCharacterSettings(level, type);
		return characterSettings["attributes"]["health"].asInt();
	}
	
	int getCharacterSpeed(classify::Level level, classify::Type type) {
		Json::Value characterSettings = Settings::getCharacterSettings(level, type);
		return characterSettings["attributes"]["speed"].asInt();
	}

	int getCharacterRange(classify::Level level, classify::Type type) {
		Json::Value characterSettings = Settings::getCharacterSettings(level, type);
		return characterSettings["attributes"]["range"].asInt();
	}

	int getCharacterDamage(classify::Level level, classify::Type type) {
		Json::Value characterSettings = Settings::getCharacterSettings(level, type);
		return characterSettings["attributes"]["damage"].asInt();
	}

	int getCharacterCount(classify::Level level, classify::Type type) {
		Json::Value characterSettings = Settings::getCharacterSettings(level, type);
		return characterSettings["count"].asInt();
	}

	int getCharacterCost(classify::Level level, classify::Type type) {
		Json::Value characterSettings = Settings::getCharacterSettings(level, type);
		return characterSettings["cost"].asInt();
	}
}
