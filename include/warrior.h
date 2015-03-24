#ifndef WARRIOR_H
#define WARRIOR_H

#include <character.h>
#include <classify.h>
#include <navigate.h>
#include <string>

class Warrior : public Character {
public:
	Warrior(navigate::Point, classify::Level);
};

class GrandWarrior : public Warrior {
public:
	GrandWarrior(navigate::Point);

	std::string toString();
};

class MasterWarrior : public Warrior {
public:

	MasterWarrior(navigate::Point);

	std::string toString();
};

class LightWarrior : public Warrior {
public:

	LightWarrior(navigate::Point);

	std::string toString();
};


class DarkWarrior : public Warrior {
public:
	DarkWarrior(navigate::Point);

	std::string toString();
};

#endif
