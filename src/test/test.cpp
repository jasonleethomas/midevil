#include <json/json.h>
#include <fstream>
#include <settings.h>
#include <classify.h>
#include <character.h>
#include <wizard.h>
#include <warrior.h>
#include <iostream>
#include <string>

using namespace characterSettings;

int main () {

	LightWizard* character = new LightWizard();

	int health = character->getHealth();
	int speed = character->getSpeed();
	int range = character->getRange();
	int damage = character->getDamage();

	std::cout << "health: " << health << std::endl
						<< "speed: " << speed << std::endl
						<< "range: " << range << std::endl
						<< "damage: " << damage << std::endl;

	delete character;
	
	return 0;
}


