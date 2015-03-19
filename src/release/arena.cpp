#include <arena.h>
#include <cell.h>
#include <object.h>
#include <character.h>
#include <obstacle.h>
#include <navigate.h>
#include <classify.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

Arena* Arena::arena = 0;

Arena::Arena() {
	this->dimensions = maxBoundary;
	this->create();
}

Arena::Arena(Point dimensions) {
	this->dimensions = dimensions;
	this->create();
}

Arena::~Arena() {
	this->destroy();
}

Arena* Arena::getArena() {
	if(arena = 0) 
		arena = new Arena();

	return arena;
}

Arena* Arena::getArena(Point dimensions) {
	if(arena = 0)
		arena = new Arena(dimensions);

	return arena;
}

void Arena::create() {
	this->cells = new Cell**[this->dimensions.x];
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		this->cells[x] = new Cell*[this->dimensions.y];
		for(uint8_t y = 0; y < this->dimensions.y; y++)
			this->cells[x][y] = new Cell({x,y});
	}	
}

void Arena::destroy() {
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		for(uint8_t y = 0; y < this->dimensions.y; y++) {
			if(this->cells[x][y] != 0) {
				if(this->cells[x][y]->getOccupant() != 0)
					delete this->cells[x][y]->getOccupant();
				delete this->cells[x][y];
			}
		}
		delete [] this->cells[x];
	}
	delete [] this->cells;

	delete arena;
}

void Arena::shuffle() {
	using std::find;

	Character* thisObject = this->animateObjects.back();
	Point thisPoint = thisObject->getPosition();
	Point thatPoint = {
		rand() % maxBoundary.x,
		rand() % maxBoundary.y
	};
	
	Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
	Cell* thatCell = this->cells[thatPoint.x][thatPoint.y];

	if(thatCell->isVacant()) {
		thisCell->vacate();
		thatCell->occupy(thisObject);
	}
	else {
		Object* thatObject = 
			this->cells[thatPoint.x][thatPoint.y]->getOccupant();

		if(thatObject->movedBy(thisObject)) {
			thisCell->vacate();
			thatCell->occupy(thisObject);
			
			vector<Character*>::iterator inactiveObject;
			inactiveObject = find(this->animateObjects.begin(), 
				this->animateObjects.end(), thatObject);
			
			this->animateObjects.erase(inactiveObject);
			delete thatObject;
		}
	}
	
	this->animateObjects.pop_back();	
	this->animateObjects.insert(this->animateObjects.end(),
		thisObject);						
}

string Arena::toString() {
	string str;
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		for(uint8_t y = 0; y < this->dimensions.y; y++) {
			if(this->cells[x][y]->isVacant())
				str += "_";
			else
				str += this->cells[x][y]->getOccupant()->toString();
		}
		str += "\n";
	}
	str += "\n";

	return str;
}
