#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
	vector<Character*> displacedObjects;
}

namespace error {
	bool flag = false;
	string message;
}

void displayArena(Cell***, Point);
void deleteArena(Cell***, Point);
void occupyArena(Cell***, Point);
bool shuffleArena(Cell***);

int main() {
	srand(time(NULL));

	Cell*** arena	= new Cell**[maxBoundary.x];

	occupyArena(arena, maxBoundary);
	displayArena(arena, maxBoundary);

	for(uint8_t tick = 0; tick < 20; tick++) {
		shuffleArena(arena);
		displayArena(arena, maxBoundary);
		sleep(1);
	}

	deleteArena(arena, maxBoundary);

	return 0;
}

bool shuffleArena(Cell*** arena) {
	using occupants::occupiedPoints;	
	using occupants::displacedObjects;

	vector<Point>::iterator thisPoint = occupiedPoints.begin();
	for(; thisPoint != occupiedPoints.end(); thisPoint++) {

		Point thatPoint = {
			rand() % (maxBoundary.x),
			rand() % (maxBoundary.y)
		};

		Cell* thisCell = arena[thisPoint->x][thisPoint->y];
		Cell* thatCell = arena[thatPoint.x][thatPoint.y];

		Character* thisObject = (Character*) thisCell->getOccupant();

		if(thatCell->isVacant()) {
			thisObject->moveTo(thatPoint);	
			thisPoint->x = thatPoint.x;
			thisPoint->y = thatPoint.y;
			thisCell->vacate();	
			thatCell->occupy(thisObject);
		}
		else {
			Character* thatObject = (Character*) thatCell->getOccupant();
			if(thatObject->movedBy(thatObject)) {
				thisObject->moveTo(thatPoint);
				thisPoint->x = thatPoint.x;
				thisPoint->y = thatPoint.y;
				thisCell->vacate();
				thatCell->occupy(thisObject);
			}
		}
	}
}

void displayArena(Cell*** arena, Point maxBoundary) {
	std::cout << std::endl;
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			if(arena[x][y]->isVacant())
				std::cout << "  ";
			else
				std::cout << arena[x][y]->getOccupant()->toString();
		}
		std::cout << std::endl;
	}
}

void deleteArena(Cell*** arena, Point maxBoundary) {	
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			Object* occupant = arena[x][y]->getOccupant();
			if(occupant != 0)
				delete occupant;
			delete arena[x][y];
		}
		delete [] arena[x];
	}	
	delete[] arena;
}	

void occupyArena(Cell*** arena, Point maxBoundary) {
	using occupants::occupiedPoints;	
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
				arena[x][y] = new Cell(here, new Character(here,
				 (Type)(cellType % 2), (Level) cellType ));
							
				occupiedPoints.push_back(here);
			}
		}
	}
}
