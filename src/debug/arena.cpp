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
			navigate::Point thisPoint;
			thisPoint.x = x;
			thisPoint.y = y;
			
			int randCell = rand() % 10;
						
			if(randCell < 2) {
				Cell* thisCell = (Cell*) new Portal(thisPoint);
				this->cells[x][y] = thisCell;
				this->animateCells.push_back(thisCell);
			}
			
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
}

Arena* Arena::getArena() {
	static Arena arena;

	return &arena;
}

void Arena::shuffle() {

	Cell* thisCell = this->animateCells.back();
	
	if(thisCell->isAnimate()) {
		Portal* thisPortal = (Portal*) thisCell;
		thisPortal->transportOccupant(this);
	}
	else {	
		Character* thisCharacter = (Character*) thisCell->getOccupant();

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
		}
	}
	
	animateCells.insert(animateCells.begin(), thisCell);
	animateCells.pop_back();
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

	std::random_shuffle(this->animateCells.begin(), 
		this->animateCells.end());
}

void Arena::occupyAnimatedCells(classify::Level level,
	classify::Type type, std::vector<navigate::Point>& points) {

	int numCharacters 
		= characterSettings::getCharacterCount(level, type);

	for(int i = 0; i < numCharacters; i++) {
		navigate::Point thisPoint = points.back();
		
		Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
		
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

		thisCell->occupy(thisObject);
		
		this->animateCells.push_back(thisCell);
	
		points.pop_back();
	}	
}

void Arena::occupyInanimateCells(
	std::vector<navigate::Point>& points) {

	int numObstacles = obstacleSettings::getObstacleCount();

	for(int i = 0; i < numObstacles; i++) {
		navigate::Point thisPoint = points.back();
		
		Cell* thisCell = this->cells[thisPoint.x][thisPoint.y];
		
		Object* thisObject = (Object*) new Obstacle(thisPoint);
		
		thisCell->occupy(thisObject);
		
		this->inanimateCells.push_back(thisCell);
		
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
