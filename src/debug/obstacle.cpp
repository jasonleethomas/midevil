#include <obstacle.h>
#include <navigate.h>
#include <object.h>

Obstacle::Obstacle(navigate::Point position) : Object(position) {}

bool Obstacle::isAnimate() {
	return false;
}

string Obstacle::toString() {
	return " XX ";
}
