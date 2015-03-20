#include <character.h>
#include <object.h>
#include <stdint.h>
#include <classify.h>
#include <navigate.h>
#include <string>

using classify::Level;
using classify::Type;
using navigate::Point;
using std::string;

Character::Character() : Object() {}

Character::Character(Point position, Type type, Level level) 
	: Object(position) {

	this->type = type;
	this->level = level;			
}

Level Character::getLevel() {
	return this->level;
}

Type Character::getType() {
	return this->type;
}

int getRange() {
	return this->range;
}

bool Character::movedBy(Object* object) {
	Character* opponent = (Character*) object;
	if(this->type != opponent->type) {
		if(this->level <= opponent->level) 
			return true;
	}

	return false;
}

bool Character::reactTo(Object* object) {
	return true;
}

void Character::moveTo(Point position) {
	this->setPosition(position);
}

string Character::toString() {
	return "C";
}
