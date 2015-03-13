#include <string.h>
#include <navigate.h>
#include <object.h>

using navigate::Position;
using std::string;

Object::Object() {
	this->id = genId();
	this->position.x = 0;
	this->position.y = 0;
}

Object::Object(Position position) {
	this->id = genId();
	this->position = position;
}

Position Object::getPosition() const {
	return this->position;
}

string Object::getId() const {
	return this->id;
}
