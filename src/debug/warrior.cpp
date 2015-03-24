#include <warrior.h>
#include <classify.h>
#include <string>

using std::string;
using navigate::Point;
using classify::Type;
using classify::Level;

Warrior::Warrior(Point position, Level level) 
	: Character(position, level, classify::Warrior) {}

GrandWarrior::GrandWarrior(Point position) 
	: Warrior(position, classify::Grand) {}

MasterWarrior::MasterWarrior(Point position) 
	: Warrior(position, classify::Master) {}

LightWarrior::LightWarrior(Point position) 
	: Warrior(position, classify::Light) {}

DarkWarrior::DarkWarrior(Point position) 
	: Warrior(position, classify::Dark) {}

string GrandWarrior::toString() {
	return " Rg ";
}

string MasterWarrior::toString() {
	return " Rm ";
}

string LightWarrior::toString() {
	return " Rl ";
}

string DarkWarrior::toString() {
	return " Rd ";
}
