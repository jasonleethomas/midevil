#include <object.h>
#include <navigate.h>
#include <string.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

using std::string;

int Object::count = 0;

Object::Object(navigate::Point position) {
	this->position = position;
	this->id = count;
	count++;
}

bool Object::operator==(const Object& other) const {
	return (this->getID() == other.getID());
}

navigate::Point Object::getPosition() const {
	return this->position;
}

void Object::setPosition(navigate::Point position) {
	this->position = position;
}

ObjectID Object::getID() const {
	return this->id;
}
