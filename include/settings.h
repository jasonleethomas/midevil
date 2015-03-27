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
		
	std::ifstream in;
	std::ofstream out;

	Settings();
	Settings(const Settings& copy);
	Settings operator=(const Settings& copy);	

	Json::Value getSettings() const;

public:		
	static Settings* getHandle();
	
	static Json::Value getGameSettings();
	static Json::Value getArenaSettings(Point);
	static Json::Value getCharacterSettings(classify::Level,
	 classify::Type);

	bool updateSettings();

	~Settings();
};

using classify::Type;
using classify::Level;

namespace gameSettings {
	int getNumPlayers();
	void setNumPlayers(int);
}

namespace playerSettings {
	Type getTeam();
	int getHP();
	
	void setTeam(Player, Type);
	void setHP(Player, int);
}

namespace arenaSettings {
	Point getDimensions();
	void setDimensions(Point);
}

namespace obstacleSettings {
	int getCount();
	void setCount(int);
}

namespace characterSettings {
	int getCharacterHealth(classify::Level, classify::Type);
	int getCharacterSpeed(classify::Level, classify::Type);
	int getCharacterRange(classify::Level, classify::Type);
	int getCharacterDamage(classify::Level, classify::Type);
	int getCharacterCount(classify::Level, classify::Type);
	int getCharacterCost(classify::Level, classify::Type);
}
