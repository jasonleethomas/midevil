#include <object.h>
#include <navigate.h>
#include <string.h>

using std::string;

int Object::count = 0;

Object::Object(navigate::Point position) {
	this->position = position;
	this->id = genId();
	count++;
}

navigate::Point Object::getPosition() const {
	return this->position;
}

void Object::setPosition(navigate::Point position) {
	this->position = position;
}

string Object::getId() const {
	return this->id;
}

string Object::genId() {
	return "";
}
