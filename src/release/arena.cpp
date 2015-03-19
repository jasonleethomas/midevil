#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <arena.h>
#include <cell.h>
#include <object.h>
#include <character.h>
#include <obstacle.h>
#include <navigate.h>
#include <classify.h>

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

Arena::Arena() {
	this->dimensions = maxBoundary;
	this->create();
}

Arena::Arena(Point dimensions) {
	this->dimensions = dimensions;
	this->create();
}

void Arena::create() {
	this->arena = new Cell**[this->dimensions.x];
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		this->arena[x] = new Cell*[this->dimensions.y];
		for(uint8_t y = 0; y < this->dimensions.y; y++)
			this->arena[x][y] = new Cell({x,y});
	}	
}

void Arena::destroy() {
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		for(uint8_t y = 0; y < this->dimensions.y; y++) {
			if(this->arena[x][y] != 0) {
				if(this->arena[x][y]->getOccupant() != 0)
					delete this->arena[x][y]->getOccupant();
				delete this->arena[x][y];
			}
		}
		delete [] this->arena[x];
	}
	delete [] this->arena;
}

void Arena::shuffle() {
	using std::find;

	Character* thisObject = this->animateObjects.back();
	Point thisPoint = thisObject->getPosition();
	Point thatPoint = {
		rand() % maxBoundary.x,
		rand() % maxBoundary.y
	};
	
	Cell* thisCell = this->arena[thisPoint.x][thisPoint.y];
	Cell* thatCell = this->arena[thatPoint.x][thatPoint.y];

	if(thatCell->isVacant()) {
		thisCell->vacate();
		thatCell->occupy(thisObject);
	}
	else {
		Object* thatObject = 
			this->arena[thatPoint.x][thatPoint.y]->getOccupant();

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
			if(this->arena[x][y]->isVacant())
				str += " ";
			else
				str += this->arena[x][y]->getOccupant()->toString();
		}
		str += "\n";
	}
	str += "\n";

	return str;
}
