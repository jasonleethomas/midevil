#include <cell.h>
#include <object.h>
#include <stdint.h>

const uint8_t XDIM = 3;
const uint8_t YDIM = 3;

Cell::Cell() {
	this->vacancy = true;
	this->position = {0,0};
	this->dimensions = {XDIM, YDIM};
	this->occupant = 0;
}

Cell::Cell(Position position) {
	this->vacancy = true;
	this->position = position;
	this->dimensions = {XDIM, YDIM};
	this->occupant = 0;
}

Cell::Cell(Position position, Object* object) {
	this->vacancy = false;	
	this->position = position;
	this->dimensions = {XDIM, YDIM};
	this->occupant = object;
}

bool Cell::isVacant() const {
	return this->vacancy;
}

bool Cell::occupy(Object* object) {
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

Dimensions Cell::getDimensions() const {
	return this->dimensions;
}

Object* Cell::getOccupant() const {
	return this->occupant;
}
