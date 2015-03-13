#include <string.h>
#include <navigate.h>
#include <object.h>

using navigate::Point;
using std::string;

Object::Object() {
	this->id = genId();
	this->position.x = 0;
	this->position.y = 0;
}

Object::Object(Point position) {
	this->id = genId();
	this->position = position;
}

Point Object::getPosition() const {
	return this->position;
}

string Object::getId() const {
	return this->id;
}
