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
	
		if(levelString == "grand")
			level = classify::Grand;
		if(levelString == "master")
			level = Master;
		if(levelString == "dark")
			level = Dark;
		if(levelString == "light")
			level = Light;

		return level;
	}

	Type stringToType(std::string typeString) {
		Type type;

		if(typeString == "warrior")
			type = Warrior;
		if(typeString == "wizard")
			type = Wizard;

		return type;
	}

	User stringToUser(std::string userString) {
		User user;

		if(userString == "first") 
			user = First;
		if(userString == "second")
			user = Second;
		if(userString == "computer")
			user = Computer;

		return user;
	}

	Mode stringToMode(std::string modeString) {
		Mode mode;
		
		if(modeString == "singleplayer")
			mode = Singleplayer;
		if(modeString == "multiplayer")
			mode = Multiplayer;
		if(modeString == "simulation")
			mode = Simulation;

		return mode;
	}
}

std::string toLower(std::string in) {
	std::string out;
	std::transform(in.begin(), in.end(), out.begin(), ::tolower);
	return out;
}

