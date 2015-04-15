#include <portal.h>
#include <arena.h>
#include <object.h>
#include <navigate.h>
#include <string>
#include <cstdlib>

Portal::Portal(navigate::Point position) : Cell(position) {}

Portal::Portal(navigate::Point position, Object* occupant) 
	: Cell(position, occupant) {}
	
void Portal::transportOccupant(Arena* arena) {
	Object* thisOccupant = this->getOccupant();
	
	navigate::Point thisPoint = this->getPosition();
	
	navigate::Point thatPoint;
	thatPoint.x = rand() % arena->dimensions.x;
	thatPoint.y = rand() % arena->dimensions.y;
	
	arena->cells[thatPoint.x][thatPoint.y]->occupy(thisOccupant);
	this->vacate();
}

bool Portal::isAnimate() {
	return true;
}

std::string Portal::toString() {
	return " >> ";
}