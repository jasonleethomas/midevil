#ifndef CLASSIFY_H
#define CLASSIFY_H
	
#include <string>

namespace classify {
	enum Level { Light, Dark, Master, Grand };
	enum Type { Warrior, Wizard };
	enum User { First, Second, Computer };
	enum Mode { Singleplayer, Multiplayer, Simulation };

	std::string levelToString(Level);
	std::string typeToString(Type);
	std::string userToString(User);
	std::string modeToString(Mode);

	Level stringToLevel(std::string);
	Type stringToType(std::string);
	User stringToUser(std::string);
	Mode modeToString(std::string);

}

#endif
