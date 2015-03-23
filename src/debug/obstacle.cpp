#include <obstacle.h>
#include <navigate.h>
#include <object.h>

Obstacle::Obstacle() : Object() {}

bool Obstacle::fights() {
	return false;
}

string Obstacle::toString() {
	return "XX";
}
