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
#include <vector>
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

Arena* Arena::arena = 0;

Arena::Arena() {

	this->dimensions = arenaSettings::getDimensions();

	this->cells = new Cell**[this->dimensions.x];
	for(int x = 0; x < this->dimensions.x; x++) {
		this->cells[x] = new Cell*[this->dimensions.y];
		for(int y = 0; y < this->dimensions.y; y++) {
			navigate::Point thisPoint;
			thisPoint.x = x;
			thisPoint.y = y;
			this->cells[x][y] = new Cell(thisPoint);
		}
	}
}

Arena::~Arena() {
	for(int x = 0; x < this->dimensions.x; x++) {
		for(int y = 0; y < this->dimensions.y; y++) 
			delete this->cells[x][y];
		delete [] this->cells[x];
	}

	delete [] this->cells;

	std::vector<Character*>::iterator thisCharacter
		= this->animateObjects.begin();
	for(; thisCharacter != this->animateObjects.end(); 
		thisCharacter++) {
		if(*thisCharacter)
			delete *thisCharacter;
	}

	std::vector<Obstacle*>::iterator thisObstacle
		= this->inanimateObjects.begin();
	for(; thisObstacle != this->inanimateObjects.end(); 
		thisObstacle++) {
		if(*thisCharacter)
			delete *thisObstacle;
	}
}

Arena* Arena::getArena() {
	static Arena arena;

	return &arena;
}

void Arena::shuffle() {

	Character* thisCharacter = animateObjects.back();

	if(!thisCharacter->isDead()) {
		for(int moves = 0; moves < thisCharacter->getSpeed(); moves++) 			{
			Point thisPoint = thisCharacter->getPosition();
			Point thatPoint;
			thatPoint.x = (thisPoint.x 
				+ (rand() % thisCharacter->getRange())) 
					% this->dimensions.x;
			thatPoint.y = (thisPoint.y 
				+ (rand() % thisCharacter->getRange())) 
					% this->dimensions.y;

			Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
			Cell* thatCell = this->cells[thatPoint.x][thatPoint.y];

			if(thatCell->isVacant()) {
				thatCell->occupy(thisCharacter);
				thisCell->vacate();
			}

			else {
				Object* thatObject = thatCell->getOccupant();
	
				if(thatObject->fights()) {
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
					}
				}
			}	
		}
	}

	animateObjects.insert(animateObjects.begin(), thisCharacter);
	animateObjects.pop_back();
}

void Arena::occupy() {
	srand(time(NULL));
	
	using namespace characterSettings;
	
	std::vector<navigate::Point> randomPoints;

	for(int x = 0; x < this->dimensions.x; x++) {
		for(int y = 0; y < this->dimensions.y; y++) {
			Point thisPoint;
			thisPoint.x = x;
			thisPoint.y = y;

			randomPoints.push_back(thisPoint);
		}
	}

	std::random_shuffle(randomPoints.begin(), randomPoints.end());
	
	occupyAnimatedCells(classify::Grand, classify::Wizard,
		randomPoints);
	occupyAnimatedCells(classify::Grand, classify::Warrior,
		randomPoints);
	occupyAnimatedCells(classify::Master, classify::Wizard,
		randomPoints);
	occupyAnimatedCells(classify::Master, classify::Warrior,
		randomPoints);
	occupyAnimatedCells(classify::Light, classify::Wizard,
		randomPoints);
	occupyAnimatedCells(classify::Light, classify::Warrior,
		randomPoints);
	occupyAnimatedCells(classify::Dark, classify::Wizard,
		randomPoints);
	occupyAnimatedCells(classify::Dark, classify::Warrior,
		randomPoints);

	occupyInanimateCells(randomPoints);

	std::random_shuffle(this->animateObjects.begin(), 
		this->animateObjects.end());
}

void Arena::occupyAnimatedCells(classify::Level level,
	classify::Type type, std::vector<navigate::Point>& points) {

	int numCharacters 
		= characterSettings::getCharacterCount(level, type);

	for(int i = 0; i < numCharacters; i++) {
		navigate::Point thisPoint = points.back();
		points.pop_back();

		Object* thisObject;

		switch(type) {
		case classify::Wizard:
			switch(level) {
				case classify::Grand:
					thisObject = 
						(Object*) new GrandWizard(thisPoint);
					break;
				case classify::Master:
					thisObject = 
						(Object*) new MasterWizard(thisPoint);				
					break;
				case classify::Light:
					thisObject = 
						(Object*) new LightWizard(thisPoint);				
					break;
				case classify::Dark:
					thisObject = 
						(Object*) new DarkWizard(thisPoint);				
					break;
			}
			Teams::wizards++;
			break;
		case classify::Warrior:
			switch(level) {
				case classify::Grand:
					thisObject = 
						(Object*) new GrandWarrior(thisPoint);				
					break;
				case classify::Master:
					thisObject = 
						(Object*) new MasterWarrior(thisPoint);				
					break;
				case classify::Light:
					thisObject = 
						(Object*) new LightWarrior(thisPoint);				
					break;
				case classify::Dark:
					thisObject = 
						(Object*) new DarkWarrior(thisPoint);				
					break;
			}
			Teams::warriors++;
			break;		
		}

		this->cells[thisPoint.x][thisPoint.y]->occupy(thisObject);
		
		this->animateObjects.push_back((Character*)thisObject);

	}	
}

void Arena::occupyInanimateCells(
	std::vector<navigate::Point>& points) {

	int numObstacles = obstacleSettings::getObstacleCount();

	for(int i = 0; i < numObstacles; i++) {
		navigate::Point thisPoint = points.back();
		points.pop_back();
		
		Object* thisObject = (Object*) new Obstacle(thisPoint);
		this->cells[thisPoint.x][thisPoint.y]->occupy(thisObject);

		this->inanimateObjects.push_back((Obstacle*) thisObject);
	}
}

bool Arena::foundWinner() {
	return (Teams::wizards < 1 || Teams::warriors < 1);
}

string Arena::getWinner() {
	if(Teams::wizards < 1)
		return "Warriors";
	else 
		return "Wizards";
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
