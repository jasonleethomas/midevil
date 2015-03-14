#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <character.h>
#include <obstacle.h>
#include <cell.h>
#include <game.h>

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

namespace occupants {
	vector<Point> occupiedPoints;
}

void displayArena(Cell***, Point);
void deleteArena(Cell***, Point);
void occupyArena(Cell***, Point);

int main() {
	srand(time(NULL));

	Cell*** arena	= new Cell**[maxBoundary.x];

	occupyArena(arena, maxBoundary);
	displayArena(arena, maxBoundary);

	for(uint8_t i = 0; i < occupants::occupiedPoints.size(); i++) {
		Point thisPoint = {
			occupants::occupiedPoints[i].x,
			occupants::occupiedPoints[i].y
		};

		Point thatPoint = {
			thatPoint.x = rand() % maxBoundary.x,
			thatPoint.y = rand() % maxBoundary.y
		};

		Cell* thisCell = arena[thisPoint.x][thisPoint.y];
		Cell* thatCell = arena[thatPoint.x][thatPoint.y];

		Character* thisObject = (Character*) thisCell->getOccupant();

		if(thatCell->isVacant()) {		
			thatCell->occupy(thisObject);
			thisObject->moveTo(thatPoint);
		}

		else {
			Object* thatObject = thatCell->getOccupant();

			if(thatObject->movedBy(thisObject)) {
				thatCell->vacate();
				thatCell->occupy(thisObject);
				thisObject->moveTo(thatPoint);

				delete thatObject;

				occupants::occupiedPoints[i] = thatPoint;
				displayArena(arena, maxBoundary);
			}
		}
	}

	deleteArena(arena, maxBoundary);

	return 0;
}

void displayArena(Cell*** arena, Point maxBoundary) {

	std::cout << std::endl;
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			if(arena[x][y]->getOccupant())
				std::cout << arena[x][y]->getOccupant()->toString();
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void deleteArena(Cell*** arena, Point maxBoundary) {
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++)
			delete arena[x][y];

		delete [] arena[x];
	}	

	delete[] arena;
}	

void occupyArena(Cell*** arena, Point maxBoundary) {
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		arena[x] = new Cell*[maxBoundary.y];

		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			Point here = {x, y};
			int cellType = rand() % 10;

			if(cellType > 5) {
				arena[x][y] = new Cell(here);
			}
			else if(cellType < 1) {
				arena[x][y] = new Cell(here, new Obstacle(here));
			}
			else {
				arena[x][y] = new Cell(here, 
					new Character(here, (Type)(cellType % 2), (Level) cellType));
							
				occupants::occupiedPoints.push_back(here);
			}
		}
	}
}
