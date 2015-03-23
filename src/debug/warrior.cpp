#include <warrior.h>
#include <classify.h>
#include <string>

using std::string;
using classify::Type;
using classify::Level;

Warrior::Warrior(Level level) : Character(level, classify::Warrior) {}

GrandWarrior::GrandWarrior() : Warrior(classify::Grand) {}

MasterWarrior::MasterWarrior() : Warrior(classify::Master) {}

LightWarrior::LightWarrior() : Warrior(classify::Light) {}

DarkWarrior::DarkWarrior() : Warrior(classify::Dark) {}

string GrandWarrior::toString() {
	return "Rg";
}

string MasterWarrior::toString() {
	return "Rm";
}

string LightWarrior::toString() {
	return "Rl";
}

string DarkWarrior::toString() {
	return "Rd";
}
