#ifndef WIZARD_H
#define WIZARD_H

#include <character.h>
#include <classify.h>
#include <string>

class Wizard : public Character {
public:
	Wizard(classify::Level);
};

class GrandWizard : public Wizard {
public:
	GrandWizard();

	std::string toString();
};

class MasterWizard : public Wizard {
public:
	MasterWizard();

	std::string toString();
};

class LightWizard : public Wizard {
public:
	LightWizard();

	std::string toString();
};

class DarkWizard : public Wizard {
public:
	DarkWizard();
		
	std::string toString();
};

#endif

