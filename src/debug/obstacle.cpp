#include <obstacle.h>
#include <navigate.h>
#include <object.h>

Obstacle::Obstacle(navigate::Point position) : Object(position) {}

bool Obstacle::fights() {
	return false;
}

string Obstacle::toString() {
	return " xx ";
}
