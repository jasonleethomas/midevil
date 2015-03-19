#ifndef WIZARD_H
#define WIZARD_H

#include <character.h>
#include <navigate.h>
#include <classify.h>
#include <string>

class Wizard : public Character {
public:
	Wizard();
	Wizard(navigate::Point, classify::Level);

	std::string toString();
};

#endif

