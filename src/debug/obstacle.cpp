#include <navigate.h>
#include <object.h>
#include <obstacle.h>

Obstacle::Obstacle() : Object() {}

Obstacle::Obstacle(navigate::Point position) : Object(position) {

}

bool Obstacle::movedBy(Object* object) {
	return false;
}

bool Obstacle::reactTo(Object* object) {
	return false;
}

string Obstacle::toString() {
	return "X";
}
