#include <stdint.h>
#include <navigate.h>
#include <object.h>
#include <cell.h>

using navigate::Position;

Cell::Cell() {
	this->vacancy = true;
	this->position.x = 0;
	this->position.y = 0;
	this->occupant = 0;
}

Cell::Cell(Position position) {
	this->vacancy = true;
	this->position = position;
	this->occupant = 0;
}

Cell::Cell(Position position, Object* object) {
	this->vacancy = false;	
	this->position = position;
	this->occupant = object;
}

bool Cell::isVacant() const {
	return this->vacancy;
}

bool Cell::occupy(Object* object) {
	if(object == 0)
		return false;

	this->occupant = object;
	this->vacancy = false;
}

bool Cell::vacate() {
	this->occupant = 0;
	this->vacancy = true;
}

Position Cell::getPosition() const {
	return this->position;
}

Object* Cell::getOccupant() const {
	return this->occupant;
}
