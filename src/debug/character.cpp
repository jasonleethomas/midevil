#include <character.h>
#include <object.h>
#include <stdint.h>
#include <classify.h>
#include <navigate.h>
#include <settings.h>
#include <string>

using namespace characterSettings;
using navigate::Point;
using classify::Level;
using classify::Type;
using std::string;

int Character::count = 0;

Character::Character(Point position, Level level, Type type) 
	: Object(position) {	
	count++;
	this->level = level;
	this->type = type;
	this->xp = 0;			

	this->dead = false;

	this->health = getCharacterHealth(this->level, this->type);
	this->damage = getCharacterDamage(this->level, this->type);
	this->range = getCharacterRange(this->level, this->type);
	this->speed = getCharacterSpeed(this->level, this->type);

	this->cost = getCharacterCost(this->level, this->type);
}

bool Character::operator==(const Character& other) const {
	return (this->getID() == other.getID());
}

Level Character::getLevel() const {
	return this->level;
}

Type Character::getType() const {
	return this->type;
}

bool Character::isDead() const {
	return this->dead;
}

int Character::getHealth() const {
	return this->health;
}

int Character::getDamage() const {
	return this->damage;
}

int Character::getRange() const {
	return this->range;
}

int Character::getSpeed() const {
	return this->speed;
}

bool Character::fights() {
	return true;
}

bool Character::attack(Character* opponent) {
	opponent->defend(this);
	if(!opponent->isDead())
		this->xp += 1;
}

void Character::defend(Character* opponent) {
	this->health -= opponent->getDamage();
	if(this->health <= 0)
		this->dead = true;
}
