#include <portal.h>
#include <obstacle.h>
#include <navigate.h> 
#include <character.h>
#include <arena.h>
#include <settings.h>
#include <string>

Portal::Portal(navigate::Point position) : Obstacle(position) {}

navigate::Point Portal::transport(Character* character) {}

std::string Portal::toString() {
	return "PP";
}
