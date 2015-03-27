#ifndef ARENA_H
#define ARENA_H

#include <list>
#include <navigate.h>
#include <classify.h>
#include <object.h>
#include <cell.h>
#include <character.h>
#include <obstacle.h>

using navigate::Point;

class Arena {
private:	
	Point dimensions;
	Cell*** cells;
	
	std::list<Character*> animateObjects;
	std::list<Obstacle*> inanimateObjects;

	Arena(Point);

	Arena(const Arena& copy);
	Arena& operator=(const Arena& copy);
	
	static Arena* arena;

public:
	static Arena* getArena(Point);

	void settings();
	void shuffle();
	void occupy();

	bool foundWinner();
	string getWinner();

	string toString();

	~Arena();
};

#endif


