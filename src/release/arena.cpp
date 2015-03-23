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
using navigate::Point;

Arena* Arena::arena = 0;

Arena::Arena(Point dimensions) {
	using navigate::minBoundary;
	using navigate::maxBoundary;

	if(dimensions.x < minBoundary.x)
		this->dimensions.x = minBoundary.x;
	else
		this->dimensions.x = dimensions.x;

	if(dimensions.y < minBoundary.y)
		this->dimensions.y = minBoundary.y;
	else
		this->dimensions.y = dimensions.y;

	if(dimensions.x > maxBoundary.x)
		this->dimensions.x = maxBoundary.x;
	else
		this->dimensions.x = dimensions.x;

	if(dimensions.y > maxBoundary.y)
		this->dimensions.y = minBoundary.y;
	else
		this->dimensions.y = dimensions.y;

	this->cells = new Cell**[this->dimensions.x];
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		this->cells[x] = new Cell*[this->dimensions.y];
		for(uint8_t y = 0; y < this->dimensions.y; y++) {
			Point thisPoint;	 
			thisPoint.x = x;
			thisPoint.y = y;
			this->cells[x][y] = new Cell(thisPoint);
		}
	}	
}

Arena::~Arena() {
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

Arena* Arena::getArena(Point dimensions) {
	if(arena = 0)
		arena = new Arena(dimensions);

	return arena;
}

void Arena::shuffle() {
	Character* thisCharacter = this->animateObjects.back();

	for(int moves = 0; moves < thisCharacter->getSpeed(); moves++) {
		Point thatPoint = {
			rand() % thisCharacter->getRange(),
			rand() % thisCharacter->getRange()
		};
	
		Cell* thatCell = this->cells[thatPoint.x][thatPoint.y];

		if(thatCell->isVacant())
			thatCell->occupy(thisCharacter);
		else {
			Object* thatObject = thatCell->getOccupant();

			if(thatObject->fights()) {
				Character* thatCharacter = (Character*) thatObject;

				thisCharacter->attack(thatCharacter);
				if(thatCharacter->isDead()) {
					thatCell->vacate();
					thatCell->occupy(thisCharacter);
				
					vector<Character*>::iterator inactiveObject;
					inactiveObject = std::find(this->animateObjects.begin(), 
						this->animateObjects.end(), thatCharacter);
			
					this->animateObjects.erase(inactiveObject);
					delete thatCharacter;
				}
			}
		}
	
		this->animateObjects.pop_back();	
		this->animateObjects.insert(this->animateObjects.end(),
			thisCharacter);
	}						
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
