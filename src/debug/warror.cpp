#include <warrior.h>
#include <navigate.h>
#include <classify.h>
#include <string>

using classify::Type;
using classify::Level;
using std::string;

const Type type = Warrior;
const defaultLevel = Novice;

Warrior::Warrior() : Character({0,0}, type, defaultLevel) {}

Warrior::Warrior(Point position, Level level) 
	: Character(position, type, level) {}

string Warrior::toString() {
	string str;
	return str;
}
