#ifndef WARRIOR_H
#define WARRIOR_H

#include <character.h>
#include <classify.h>
#include <string>

class Warrior : public Character {
public:
	Warrior(classify::Level);
};

class GrandWarrior : public Warrior {
public:
	GrandWarrior();

	std::string toString();
};

class MasterWarrior : public Warrior {
public:

	MasterWarrior();

	std::string toString();
};

class LightWarrior : public Warrior {
public:

	LightWarrior();

	std::string toString();
};


class DarkWarrior : public Warrior {
public:
	DarkWarrior();

	std::string toString();
};

#endif
