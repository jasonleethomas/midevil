#include <object.h>
#include <navigate.h>
#include <string.h>

using std::string;

int Object::count = 0;

Object::Object() {
	this->id = genId();
	count++;
}

string Object::getId() const {
	return this->id;
}

string Object::genId() {
	return "";
}
