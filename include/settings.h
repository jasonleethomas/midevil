#include <json/json.h>
#include <iostream>
#include <fstream>
#include <string>
#include <classify.h>
#include <navigate.h>
#include <game.h>
#include <player.h>
#include <arena.h>
#include <object.h>
#include <obstacle.h>
#include <character.h>

class Settings {
private:	
	static Settings handle;
	static const char* filename;

	Json::Value settings;
	Json::Value defaultSettings;	

	std::ifstream in;
	std::ofstream out;

	Settings();
	Settings(const Settings& copy);
	Settings operator=(const Settings& copy);	

	Json::Value getSettings() const;
	void setSettings(Json::Value);
	void updateSettings();

public:		
	static Settings* getHandle();
	void revertSettings();

	static Json::Value getArenaSettings();	
	static Json::Value getCellSettings();
	static Json::Value getCharacterSettings(classify::Level,
	 classify::Type);
	static Json::Value getGameSettings();
	static Json::Value getObstacleSettings();
	static Json::Value getPlayerSettings(classify::User);

	static void setArenaSettings(Json::Value);
	static void setCellSettings(Json::Value);
	static void setCharacterSettings(classify::Level, 
		classify::Type, Json::Value);
	static void setGameSettings(Json::Value);
	static void setObstacleSettings(Json::Value);
	static void setPlayerSettings(classify::User, Json::Value);

	~Settings();
};

namespace arenaSettings {
	navigate::Point getDimensions();
	void setDimensions(navigate::Point);
}

namespace cellSettings {}

namespace characterSettings {
	int getCharacterHealth(classify::Level, classify::Type);
	int getCharacterSpeed(classify::Level, classify::Type);
	int getCharacterRange(classify::Level, classify::Type);
	int getCharacterDamage(classify::Level, classify::Type);
	int getCharacterCount(classify::Level, classify::Type);
	int getCharacterCost(classify::Level, classify::Type);

	void setCharacterCost(classify::Level, classify::Type, int);
	void setCharacterCount(classify::Level, classify::Type, int);
}

namespace gameSettings {
	void setMode(classify::Mode);
	classify::Mode getMode();
}

namespace obstacleSettings {
	int getObstacleCount();
	void setObstacleCount(int);
}

namespace playerSettings {
	classify::Type getTeam(classify::User);
	int getCoin(classify::User);
	void setTeam(classify::User, classify::Type);
	void setCoin(classify::User, int);
}

std::string intToString(int);
