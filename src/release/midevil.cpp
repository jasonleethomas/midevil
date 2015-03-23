#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <navigate.h>
#include <classify.h>
#include <arena.h>
#include <cell.h>
#include <object.h>
#include <character.h>
#include <wizard.h>
#include <warrior.h>
#include <obstacle.h>

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

namespace error {
	bool flag = false;
	string message;
}

void occupyArena(Cell***, Point);

int main() {

	Arena* arena = Arena::getArena(maxBoundary);
	return 0;
}


/*

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

*/
