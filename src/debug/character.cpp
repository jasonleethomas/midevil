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

Character::Character(Point position, Type type, Level level) 
	: Object(position) {

	this->type = type;
	this->level = level;
	this->xp = 0;			
}

Level Character::getLevel() {
	return this->level;
}

Type Character::getType() {
	return this->type;
}

int Character::getRange() {
	return this->range;
}

int Character::getSpeed() {
	return this->speed;
}

void Character::levelUp() {
	
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
