#include <arena.h>
#include <cell.h>
#include <object.h>
#include <character.h>
#include <warrior.h>
#include <wizard.h>
#include <obstacle.h>
#include <navigate.h>
#include <classify.h>
#include <settings.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using std::list;
using navigate::Point;

namespace Teams {
	int wizards = 0;
	int warriors = 0;
}

std::string intToString(int num);

Arena* Arena::arena = 0;

Arena::Arena(Point dimensions) {

	this->dimensions = dimensions;

	this->cells = new Cell**[this->dimensions.x];
	for(int x = 0; x < this->dimensions.x; x++) {
		this->cells[x] = new Cell*[this->dimensions.y];
		for(int y = 0; y < this->dimensions.y; y++) {
			Point thisPoint;	 
			thisPoint.x = x;
			thisPoint.y = y;
			this->cells[x][y] = new Cell(thisPoint);
		}
	}	
}

Arena::~Arena() {
	for(int x = 0; x < this->dimensions.x; x++) {
		for(int y = 0; y < this->dimensions.y; y++) {
			if(this->cells[x][y]->getOccupant() != 0)
				delete this->cells[x][y]->getOccupant();
			delete this->cells[x][y];
		}
		delete [] this->cells[x];
	}

	delete [] this->cells;
}

Arena* Arena::getArena(Point dimensions) {
	if(arena == 0)
		arena = new Arena(dimensions);

	return arena;
}

void Arena::shuffle() {
	Character* thisCharacter = this->animateObjects.front();

//	for(int moves = 0; moves < thisCharacter->getSpeed(); moves++) {
		Point thisPoint = thisCharacter->getPosition();
		Point thatPoint;
		thatPoint.x = (thisPoint.x 
			+ (rand() % thisCharacter->getRange())) % this->dimensions.x;
		thatPoint.y = (thisPoint.y 
			+ (rand() % thisCharacter->getRange())) % this->dimensions.y;
		
		Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
		Cell* thatCell = this->cells[thatPoint.x][thatPoint.y];

		if(thatCell->isVacant()) {
			thatCell->occupy(thisCharacter);
			thisCell->vacate();
		}
		else {
			Object* thatObject = thatCell->getOccupant();
					
			if(thatObject && thatObject->fights()) {
				Character* thatCharacter = (Character*) thatObject;

				thisCharacter->attack(thatCharacter);
				if(thatCharacter->isDead()) {
					thatCell->vacate();
					thatCell->occupy(thisCharacter);
					thisCell->vacate();

					switch(thatCharacter->getType()) {
					case classify::Warrior:
						Teams::warriors--;
						break;
					case classify::Wizard:
						Teams::wizards--;
						break;
					}
				
					list<Character*>::iterator inactiveObject;
					inactiveObject = std::find(this->animateObjects.begin(), 
						this->animateObjects.end(), thatCharacter);
			
					this->animateObjects.erase(inactiveObject);
					//delete thatCharacter;
				}
			}
		}	
	//}		

	this->animateObjects.push_back(thisCharacter);
	this->animateObjects.pop_front();
					
}

void Arena::occupy() {
	srand(time(NULL));

	for(int x = 0; x < this->dimensions.x; x++) {
		for(int y = 0; y < this->dimensions.y; y++) {
			
			Point thisPoint = {x, y};
			int objectSeed = rand()	% 10;
			
			if(objectSeed >= 5) { 

				Character* randCharacter;

				int typeSeed = rand() % 10;
				
				if(typeSeed >= 5) { 
					int levelSeed = rand() % 10;					
							
					if(levelSeed >= 7) 
						randCharacter = (Character*) new LightWarrior(thisPoint);
					else if(levelSeed >= 4) 
						randCharacter = (Character*) new DarkWarrior(thisPoint);
					else if(levelSeed >= 2) 
						randCharacter = (Character*) new MasterWarrior(thisPoint);
					else 
						randCharacter = (Character*) new GrandWarrior(thisPoint);

					Teams::warriors++;
				}	
				else {
					int levelSeed = rand() % 10;					

					if(levelSeed >= 7) 
						randCharacter = (Character*) new LightWizard(thisPoint);
					else if(levelSeed >= 4) 
						randCharacter = (Character*) new DarkWizard(thisPoint);
					else if(levelSeed >= 2) 
						randCharacter = (Character*) new MasterWizard(thisPoint);
					else 
						randCharacter = (Character*) new GrandWizard(thisPoint);

					Teams::wizards++;
				}						
				
				this->cells[x][y]->occupy(randCharacter);
				animateObjects.push_back(randCharacter);
					
			}
			else if(objectSeed < 1) {
				Obstacle* randObstacle = new Obstacle(thisPoint);

				this->cells[x][y]->occupy(randObstacle);
				inanimateObjects.push_back(randObstacle);
			}
		}
	}
}

bool Arena::foundWinner() {
	return (Teams::wizards == 0 || Teams::warriors == 0);
}

classify::Type Arena::getWinner() {
	if(Teams::wizards == 0)
		return classify::Wizard;
	else 
		return classify::Warrior;
}

string Arena::toString() {
	string str = "\n";
	for(uint8_t x = 0; x < this->dimensions.x; x++) {
		for(uint8_t y = 0; y < this->dimensions.y; y++) {
			if(this->cells[x][y]->isVacant())
				str += " __ ";
			else
				str += this->cells[x][y]->getOccupant()->toString();
		}
		str += "\n\n";
	}
	
	str += "Wizards: ";
	str += intToString(Teams::wizards);
	str += "\n";
	str += "Warriors: ";
	str += intToString(Teams::warriors);
	str += "\n";

	return str;
}

std::string intToString(int num) {
	std::ostringstream ostr;
	ostr << num;
	std::string cstr = ostr.str();

	return cstr;	
}
