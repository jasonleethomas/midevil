#ifndef WARRIOR_H
#define WARRIOR_H

#include <character.h>
#include <navigate.h>
#include <classify.h>
#include <string>

class Warrior : public Character {
public:
	Warrior();
	Warrior(navigate::Point, classify::Level);
	
	std::string toString();
};

#endif
