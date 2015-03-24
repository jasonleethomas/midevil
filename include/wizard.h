#ifndef WIZARD_H
#define WIZARD_H

#include <character.h>
#include <classify.h>
#include <navigate.h>
#include <string>

class Wizard : public Character {
public:
	Wizard(navigate::Point, classify::Level);
};

class GrandWizard : public Wizard {
public:
	GrandWizard(navigate::Point);

	std::string toString();
};

class MasterWizard : public Wizard {
public:
	MasterWizard(navigate::Point);

	std::string toString();
};

class LightWizard : public Wizard {
public:
	LightWizard(navigate::Point);

	std::string toString();
};

class DarkWizard : public Wizard {
public:
	DarkWizard(navigate::Point);
		
	std::string toString();
};

#endif

