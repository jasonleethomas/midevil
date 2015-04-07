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

Settings Settings::handle;

Settings::Settings() {
	this->in.open(filename);
	this->in >> this->settings;
	this->in.close();

	this->defaultSettings = this->settings;
}

Settings::~Settings() {
//	this->revertSettings();
}

Settings* Settings::getHandle() {
	return &handle;
}

void Settings::revertSettings() {
	this->out.open(filename, std::ofstream::out);
	this->out << this->defaultSettings;
	this->out.close();
}

Json::Value Settings::getSettings() const {
	return this->settings;
}

void Settings::setSettings(Json::Value settings) {

	this->settings = settings;
	this->out.open(filename, std::ofstream::out);
	this->out << this->settings; // bad, bad news
	this->out.close();
}

void Settings::updateSettings() {
	this->in.open(filename);
	this->in >> this->settings;
	this->in.close();	
}

Json::Value Settings::getGameSettings() {

	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();
	Json::Value gameSettings = settings["game"];

	return gameSettings;
}

Json::Value Settings::getArenaSettings() {

	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();
	Json::Value arenaSettings = settings["arena"];

	return arenaSettings;
}

Json::Value Settings::getPlayerSettings(classify::User user) {

	std::string userstring = classify::userToString(user);
	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();
	Json::Value playerSettings = settings["player"];

	return playerSettings[userstring];
}

Json::Value Settings::getCharacterSettings(classify::Level level, 
	classify::Type type) {

	std::string levelString = classify::levelToString(level);
	std::string typeString = classify::typeToString(type);
	Settings* handle = getHandle();
	Json::Value settings = handle->getSettings();	
	Json::Value characterSettings = settings["character"];
	
	return characterSettings[typeString][levelString];
}

void Settings::setGameSettings(Json::Value gameSettings) {

	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();	
	settings["game"] = gameSettings;

	handle->setSettings(settings);
}

void Settings::setArenaSettings(Json::Value arenaSettings) {

	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();
	settings["arena"] = arenaSettings;

	handle->setSettings(settings);
}

void Settings::setPlayerSettings(classify::User user,
	Json::Value playerSettings ) {

	std::string userString = classify::userToString(user);
	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();
	settings["player"][userString] = playerSettings;

	handle->setSettings(settings);
}


void Settings::setCharacterSettings(classify::Level level, 
	classify::Type type, Json::Value characterSettings) {

	std::string levelString = classify::levelToString(level);
	std::string typeString = classify::typeToString(type);
	Settings* handle = Settings::getHandle();
	Json::Value settings = handle->getSettings();
	settings["character"][typeString][levelString] 
		= characterSettings;

	handle->setSettings(settings);
}

namespace gameSettings {
	void setMode(classify::Mode mode) {

		Json::Value gameSettings = Settings::getGameSettings();
		std::string modeString = classify::modeToString(mode);
		gameSettings["mode"] = modeString;

		Settings::setGameSettings(gameSettings);
	}

	classify::Mode getMode() {

		Json::Value gameSettings = Settings::getGameSettings();
		std::string modeString = gameSettings["mode"].asString();
		classify::Mode mode = classify::stringToMode(modeString);

		return mode;
	}
}

namespace playerSettings {

	classify::Type getTeam(classify::User user) {

		Json::Value playerSettings = Settings::getPlayerSettings(user);
		std::string typeString = playerSettings["team"].asString();
		classify::Type team = classify::stringToType(typeString);

		return team;		
	}

	void setTeam(classify::User user, classify::Type team) {

		Json::Value playerSettings = Settings::getPlayerSettings(user);
		std::string typeString = typeToString(team);
		playerSettings["team"] = typeString;

		Settings::setPlayerSettings(user, playerSettings);
	}

	int getCoin(classify::User user) {

		Json::Value playerSettings = Settings::getPlayerSettings(user);
		int coin = playerSettings["coin"].asInt();

		return coin;
	}

	void setCoin(classify::User user, int coin) {

		Json::Value playerSettings = Settings::getPlayerSettings(user);
		playerSettings["coin"] = coin;

		Settings::setPlayerSettings(user, playerSettings);
	}
}

namespace arenaSettings {
	navigate::Point getDimensions() {

		Json::Value arenaSettings = Settings::getArenaSettings();		
		navigate::Point dimensions;
		dimensions.x = arenaSettings["dimensions"]["x"].asInt();
		dimensions.y = arenaSettings["dimensions"]["y"].asInt();

		return dimensions;
	}

	void setDimensions(navigate::Point dimensions) {

		Json::Value arenaSettings = Settings::getArenaSettings();
		arenaSettings["dimensions"]["x"] = dimensions.x;
		arenaSettings["dimensions"]["y"] = dimensions.y;

		Settings::setArenaSettings(arenaSettings);
	}
}

namespace obstacleSettings {
	int getCount() {}
}

namespace characterSettings {
	using classify::Level;
	using classify::Type;

	int getCharacterHealth(classify::Level level,
		classify::Type type) {

		Json::Value characterSettings 
			= Settings::getCharacterSettings(level, type);

		return characterSettings["attributes"]["health"].asInt();
	}
	
	int getCharacterSpeed(classify::Level level, 
		classify::Type type) {

		Json::Value characterSettings 
			= Settings::getCharacterSettings(level, type);

		return characterSettings["attributes"]["speed"].asInt();
	}

	int getCharacterRange(classify::Level level, 
		classify::Type type) {

		Json::Value characterSettings 
			= Settings::getCharacterSettings(level, type);

		return characterSettings["attributes"]["range"].asInt();
	}

	int getCharacterDamage(classify::Level level, 
		classify::Type type) {

		Json::Value characterSettings 
			= Settings::getCharacterSettings(level, type);

		return characterSettings["attributes"]["damage"].asInt();
	}

	int getCharacterCount(classify::Level level, 
		classify::Type type) {

		Json::Value characterSettings 
			= Settings::getCharacterSettings(level, type);

		return characterSettings["count"].asInt();
	}

	int getCharacterCost(classify::Level level, 
		classify::Type type) {

		Json::Value characterSettings 
			= Settings::getCharacterSettings(level, type);

		return characterSettings["cost"].asInt();
	}

	void setCharacterCost(classify::Level level,
		classify::Type type, int cost) {

		Json::Value characterSettings =
			Settings::getCharacterSettings(level, type);
		characterSettings["cost"] = cost;

		Settings::setCharacterSettings(level, type, characterSettings);
	}

	void setCharacterCount(classify::Level level,
		classify::Type type, int count) {

		Json::Value characterSettings = 
			Settings::getCharacterSettings(level, type);
		characterSettings["count"] = count;

		Settings::setCharacterSettings(level, type, characterSettings);
	}
}

std::string intToString(int num) {
	std::ostringstream ostr;
	ostr << num;
	std::string cstr = ostr.str();

	return cstr;	
}
