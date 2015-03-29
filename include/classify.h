#ifndef CLASSIFY_H
#define CLASSIFY_H
	
#include <string>

namespace classify {
	enum Level { Light, Dark, Master, Grand };
	enum Type { Warrior, Wizard };
	enum User { First, Second, Computer };
	enum Mode { Singleplayer, Multiplayer, Simulation };

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
}

#endif
