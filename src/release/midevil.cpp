#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <character.h>
#include <wizard.h>
#include <warrior.h>
#include <obstacle.h>
#include <cell.h>
#include <game.h>

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

namespace occupants {
	vector<Point> activePoints;
	vector<Character*> activeObjects;
	vector<Character*> inactiveObjects;
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
	using occupants::activeObjects;
	srand(time(NULL));

	Cell*** arena	= new Cell**[maxBoundary.x];

	occupyArena(arena, maxBoundary);
	displayArena(arena, maxBoundary);

	while(activeObjects.size() > 1) {
		shuffleArena(arena);
		displayArena(arena, maxBoundary);
		usleep(500000);
	}

	deleteArena(arena, maxBoundary);

	return 0;
}

void occupyArena(Cell*** arena, Point maxBoundary) {	
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		arena[x] = new Cell*[maxBoundary.y];
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			Point thisPoint = {x, y};
			uint8_t randSeed = rand() % 10;

			if(randSeed < 1) 
				arena[x][y] = new Cell(thisPoint, new Obstacle(thisPoint));
			else if(randSeed > 5) {
				Level randLevel = (Level) (rand() % 3);

				Character* randCharacter;
				Type randType = (Type) (rand() % 2);

				if(randType == classify::Warrior)
					randCharacter = new Warrior(thisPoint, randLevel);
				else
					randCharacter = new Wizard(thisPoint, randLevel);

				arena[x][y] = new Cell(thisPoint, randCharacter);

				occupants::activeObjects.push_back(randCharacter);
			}
			else 
				arena[x][y] = new Cell(thisPoint);
		}
	}	
}

void displayArena(Cell*** arena, Point maxBoundary) {
	using occupants::activeObjects;
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			if(arena[x][y]->isVacant())
				std::cout << "  ";
			else
				std::cout << arena[x][y]->getOccupant()->toString();
		}
		std::cout << std::endl;
	}
	std::cout << "Active objects :" << activeObjects.size() << std::endl;
	std::cout << std::endl;
}

bool shuffleArena(Cell*** arena) {
	using std::find;
	using occupants::activeObjects;
	using occupants::inactiveObjects;

	Character* thisObject = activeObjects.back();
	Point thisPoint = thisObject->getPosition();
	Point thatPoint = {
		rand() % maxBoundary.x,
		rand() % maxBoundary.y
	};
	
	Cell* thisCell = arena[thisPoint.x][thisPoint.y];
	Cell* thatCell = arena[thatPoint.x][thatPoint.y];

	if(thatCell->isVacant()) {
		thisCell->vacate();
		thatCell->occupy(thisObject);
	}
	else {
		Object* thatObject = 
			arena[thatPoint.x][thatPoint.y]->getOccupant();

		if(thatObject->movedBy(thisObject)) {
			thisCell->vacate();
			thatCell->occupy(thisObject);
			
			vector<Character*>::iterator inactiveObject;
			inactiveObject = find(activeObjects.begin(), 
				activeObjects.end(), (Character*)thatObject);
			
			activeObjects.erase(inactiveObject);
			delete thatObject;
		}
	}
	
	activeObjects.pop_back();	
	activeObjects.insert(activeObjects.begin(), thisObject);						
}

void deleteArena(Cell*** arena, Point maxBoundary) {	
	using occupants::inactiveObjects;
	for(uint8_t x = 0; x < maxBoundary.x; x++) {
		for(uint8_t y = 0; y < maxBoundary.y; y++) {
			if(arena[x][y] != 0) {
				if(arena[x][y]->getOccupant() != 0)
					delete arena[x][y]->getOccupant();
				delete arena[x][y];
			}
		}
		delete [] arena[x];
	}
	delete [] arena;
}
