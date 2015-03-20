#include <warrior.h>
#include <classify.h>
#include <string>

using std::string;

Warrior::Warrior() : Character({0,0}, classify::Warrior,
	classify::Novice) {}

Warrior::Warrior(Point position, Level level) 
	: Character(position, classify::Warrior, level) {}

string Warrior::toString() {
	string str;

	switch(this->getLevel()) {
	case classify::Grand:
		str += "G"; break;
	case classify::Master:
		str += "M"; break;
	case classify::Novice:		
		str += "N"; break;
	default:
		str += "N"; break;
	}

	str += "R";

	return str;
}
