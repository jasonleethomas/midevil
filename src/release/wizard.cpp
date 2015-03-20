#include <wizard.h>
#include <classify.h>
#include <string>

using std::string;

Wizard::Wizard() : Character({0,0}, classify::Wizard,
	classify::Novice) {}

Wizard::Wizard(Point position, Level level) 
	: Character(position, classify::Wizard, level) {}

string Wizard::toString() {
	string str;

	switch(this->level) {
	case classify::Grand:
		str += "G"; break;
	case classify::Master:
		str += "M"; break;
	case classify::Novice:		
		str += "N"; break;
	default:
		str += "N"; break;
	}

	str += "Z";

	return str;
}
