#include <stdint.h>
#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <character.h>

using classify::Level;
using classify::Type;
using navigate::Point;

Character::Character() : Object() {}

Character::Character(Point position, Type type, Level level) 
	: Object(position) {

	this->type = type;
	this->level = level;			
}

bool Character::movedBy(Character* object) {
	if(this->type == object->type) {
		if(this->level <= object->level) 
			return true;
	}

	return false;
}

void Character::moveTo(Point position) {
	this->position = position;
}
