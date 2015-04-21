#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <cell.h>
#include <character.h>
#include <obstacle.h>

using navigate::Point;

class Arena {
friend class Portal;
private:	
	static Arena* arena;
	Point dimensions;
	Cell*** cells;
	
	std::vector<Cell*> portals;
	std::vector<Character*> characters;
	std::vector<Obstacle*> obstacles;
	
	Arena();
	Arena(const Arena& copy);
	Arena& operator=(const Arena& copy);
	
	void occupyCharacters(classify::Level, classify::Type,
		std::vector<navigate::Point>&);
	void occupyObstacles(std::vector<navigate::Point>&);

public:
	static Arena* getArena();

	void settings();
	void shuffle();
	void occupy();
	void empty();

	bool foundWinner();
	string getWinner();

	string toString();

	~Arena();
};

#endif


