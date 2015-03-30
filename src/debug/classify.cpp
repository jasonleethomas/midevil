#include <classify.h>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>

std::string toLower(std::string str);

namespace classify {
std::string levelToString(Level level) {
		std::string levelString;
		
		switch(level) {
		case Grand:
			levelString = "grand";	
			break;
		case Master:
			levelString = "master"; 
			break;
		case Light:
			levelString = "light";
			break;
		case Dark:
			levelString = "dark";	
			break;
		}

		return levelString;
	}

	std::string typeToString(Type type) {
		std::string typeString;

	 	switch(type) { 
		case Warrior: 		
			typeString = "warrior";	 		
			break; 	
		case Wizard:
			typeString = "wizard";
	 		break; 	
		}	

		return typeString;
	}

	std::string userToString(User user)	{
		std::string userString;

		switch(user) {
		case First:
			userString = "first";
			break;
		case Second:
			userString = "second";
			break;
		case Computer:
			userString = "computer";
			break;
		}
		
		return userString;
	}

	std::string modeToString(Mode mode) {
		std::string modeString;

		switch(mode) {
		case Singleplayer:
			modeString = "singleplayer";
			break;
		case Multiplayer:
			modeString = "multiplayer";
			break;
		case Simulation:
			modeString = "simulation";
			break;
		}

		return modeString;
	}

	Level stringToLevel(std::string levelString) {
		Level level;
	
		if(toLower(levelString) == "grand")
			level = Grand;
		if(toLower(levelString) == "master")
			level = Master;
		if(toLower(levelString) == "dark")
			level = Dark;
		if(toLower(levelString) == "light")
			level = Light;

		return level;
	}

	Type stringToType(std::string typeString) {
		Type type;

		if(toLower(typeString) == "warrior")
			type = Warrior;
		if(toLower(typeString) == "wizard")
			type = Wizard;

		return type;
	}

	User stringToUser(std::string userString) {
		User user;

		if(toLower(userString) == "first") 
			user = First;
		if(toLower(userString) == "second")
			user = Second;
		if(toLower(userString) == "computer")
			user = Computer;

		return user;
	}

	Mode stringToMode(std::string modeString) {
		Mode mode;
		
		if(toLower(modeString) == "singleplayer")
			mode = Singleplayer;
		if(toLower(modeString) == "multiplayer")
			mode = Multiplayer;
		if(toLower(modeString) == "simulation")
			mode = Simulation;

		return mode;
	}
}

std::string toLower(std::string in) {
	std::string out;
	std::transform(in.begin(), in.end(), out.begin(), ::tolower);
	return out;
}

