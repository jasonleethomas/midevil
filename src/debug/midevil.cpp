#include <iostream>
#include <json/json.h>
#include <stdlib.h>
#include <time.h>

#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <character.h>
#include <obstacle.h>
#include <cell.h>
#include <game.h>

using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

int main() {
	srand(time(NULL));

	Cell*** arena = new Cell**[maxBoundary.x];
	for(uint8_t x = 0; x <= maxBoundary.x; x++) {
		arena[x] = new Cell*[maxBoundary.y];
		for(uint8_t y = 0; y <= maxBoundary.y; y++) {
			Point here = {x, y};
			int cellType = rand() % 3;
			switch(cellType) {
			case 0:
				arena[x][y] = new Cell(here);	
				break;
			case 1:
				arena[x][y] = new Cell(here, 
					new Character(here, (Type)(cellType % 2), (Level) cellType));
				break;
			case 2:
				arena[x][y] = new Cell(here, new Obstacle(here));
				break;
			}
			
			delete arena[x][y];
		}

		delete [] arena[x];
	}

	delete [] arena;

	return 0;
}




void displayCell(Cell* cell, Point maxBoundary) {
	Object* object = cell->getOccupant();
	if(object)
		object->display();
}
