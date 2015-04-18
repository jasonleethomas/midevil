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
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <portal.h>

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
			Cell* thisCell;			
			navigate::Point thisPoint;
			thisPoint.x = x;
			thisPoint.y = y;
			
			int randCell = rand() % 10;
			// 1/10 chance of cell being a portal			
			if(randCell < 1) {
				thisCell = (Cell*) new Portal(thisPoint);
				this->portals.push_back(thisCell);
			}
			else
				thisCell = new Cell(thisPoint);

			this->cells[x][y] = thisCell;
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
		= this->characters.begin();
	for(; thisCharacter != this->characters.end(); thisCharacter++) {
		if(*thisCharacter)
			delete *thisCharacter;
	}
}

Arena* Arena::getArena() {
	static Arena arena;

	return &arena;
}

void Arena::shuffle() {

	Character* thisCharacter = this->characters.back();

	if(!thisCharacter->isDead()) {
		for(int moves = 0; moves < thisCharacter->getSpeed(); 
			moves++) {

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

				if(thatObject->isAnimate()) {
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

		this->characters.insert(this->characters.begin(),
			thisCharacter);
	}

	this->characters.pop_back();

	std::vector<Cell*>::iterator itr = this->portals.begin();

	for(; itr != this->portals.end(); itr++) {
		Portal* thisPortal = (Portal*) *itr;
		thisPortal->transportOccupant(this);
	}
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
	
	occupyCharacters(classify::Grand, classify::Wizard,
		randomPoints);
	occupyCharacters(classify::Grand, classify::Warrior,
		randomPoints);
	occupyCharacters(classify::Master, classify::Wizard,
		randomPoints);
	occupyCharacters(classify::Master, classify::Warrior,
		randomPoints);
	occupyCharacters(classify::Light, classify::Wizard,
		randomPoints);
	occupyCharacters(classify::Light, classify::Warrior,
		randomPoints);
	occupyCharacters(classify::Dark, classify::Wizard,
		randomPoints);
	occupyCharacters(classify::Dark, classify::Warrior,
		randomPoints);

	occupyObstacles(randomPoints);

	std::random_shuffle(this->characters.begin(), 
		this->characters.end());
}

void Arena::occupyCharacters(classify::Level level,
	classify::Type type, std::vector<navigate::Point>& points) {

	int numCharacters 
		= characterSettings::getCharacterCount(level, type);

	for(int i = 0; i < numCharacters; i++) {
		navigate::Point thisPoint = points.back();
		
		Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
		
		Character* thisCharacter;

		switch(type) {
		case classify::Wizard:
			switch(level) {
				case classify::Grand:
					thisCharacter = new GrandWizard(thisPoint);
					break;
				case classify::Master:
					thisCharacter = new MasterWizard(thisPoint);				
					break;
				case classify::Light:
					thisCharacter = new LightWizard(thisPoint);				
					break;
				case classify::Dark:
					thisCharacter = new DarkWizard(thisPoint);				
					break;
			}
			Teams::wizards++;
			break;
		case classify::Warrior:
			switch(level) {
				case classify::Grand:
					thisCharacter = new GrandWarrior(thisPoint);				
					break;
				case classify::Master:
					thisCharacter = new MasterWarrior(thisPoint);				
					break;
				case classify::Light:
					thisCharacter = new LightWarrior(thisPoint);				
					break;
				case classify::Dark:
					thisCharacter = new DarkWarrior(thisPoint);				
					break;
			}
			Teams::warriors++;
			break;		
		}

		thisCell->occupy((Object*) thisCharacter);
		
		this->characters.push_back(thisCharacter);
	
		points.pop_back();
	}	
}

void Arena::occupyObstacles(
	std::vector<navigate::Point>& points) {

	int numObstacles = obstacleSettings::getObstacleCount();

	for(int i = 0; i < numObstacles; i++) {
		navigate::Point thisPoint = points.back();
		
		Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
		
		Obstacle* thisObstacle = new Obstacle(thisPoint);
		
		thisCell->occupy((Object*) thisObstacle);
		
		this->obstacles.push_back(thisObstacle);
		
		points.pop_back();
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
				str += this->cells[x][y]->toString();
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
