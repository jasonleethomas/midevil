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
}

namespace error {
	bool flag = false;
	string message;
}

bool shuffleArena(Cell (*)[][maxBoundary.y]);
void displayArena(Cell (*)[][maxBoundary.y], Point maxBoundary);
void deleteArena(Cell (*)[][maxBoundary.y], Point maxBoundary);	
void occupyArena(Cell (*)[][maxBoundary.y], Point maxBoundary);

int main() {
	srand(time(NULL));

	Cell* arena[maxBoundary.x][maxBoundary.y];

	occupyArena(arena, maxBoundary);
	displayArena(arena, maxBoundary);

	for(uint8_t tick = 0; tick < 20; tick++) {
		shuffleArena(arena);
		sleep(1);
	}

	displayArena(arena, maxBoundary);
	deleteArena(arena, maxBoundary);

	return 0;
}

bool shuffleArena(Cell (*arena)[][maxBoundary.y]) {
	using occupants::occupiedPoints;	
	
	for(uint8_t i = 0; i < occupiedPoints.size()-1; i++) {

		Point thisPoint = {
			occupiedPoints[i].x,
			occupiedPoints[i].y
		};

		Point thatPoint = {
			rand() % maxBoundary.x,
			rand() % maxBoundary.y
		};

		Cell* thisCell = arena[thisPoint.x][thisPoint.y];
		Cell* thatCell = arena[thatPoint.x][thatPoint.y];

		Character thisObject = (Character*) thisCell->getOccupant();

		if(thatCell->isVacant()) {
			thisObject->moveTo(thatPoint);	
			//thatCell->occupy(thisObject);
			thisCell->vacate();	
		}
	}
}

void displayArena(Cell (*arena)[][maxBoundary.y], Point maxBoundary) {
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

void deleteArena(Cell (*arena)[][maxBoundary.y], Point maxBoundary) {	
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			Object* occupant = arena[x][y]->getOccupant();
			if(occupant != 0)
				delete occupant;
			delete arena[x][y];
		}
	}	
}	

void occupyArena(Cell (*arena)[][maxBoundary.y], Point maxBoundary) {
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			Point here = {x, y};
			int cellType = rand() % 10;

			if(cellType > 5) 
				arena[x][y] = new Cell(here);
			else if(cellType < 1) 
				arena[x][y] = new Cell(here, new Obstacle(here));
			else {
				arena[x][y] = new Cell(here, 
					new Character(here, (Type)(cellType % 2),
					 (Level) cellType));
							
				occupants::occupiedPoints.push_back(here);
			}
		}
	}
}
