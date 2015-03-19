#include <character.h>
#include <object.h>
#include <stdint.h>
#include <string.h>
#include <navigate.h>
#include <classify.h>

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
	this->position = position;
}

string Character::toString() {
	return "C";
}
