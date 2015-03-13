#include <stdint.h>
#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <character.h>

using classify::Level;
using classify::Type;
using navigate::Position;

Character::Character() : Object() {}

Character::Character(Position position, Type type, Level level) 
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

void Character::moveTo(Position position) {
	this->position = position;
}
