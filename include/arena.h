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
private:	
	static Arena* arena;
	Point dimensions;
	Cell*** cells;
	
	std::vector<Character*> animateObjects;
	std::vector<Obstacle*> inanimateObjects;

	Arena();
	Arena(const Arena& copy);
	Arena& operator=(const Arena& copy);
	
	void occupyAnimatedCells(classify::Level, classify::Type,
		std::vector<navigate::Point>&);
	void occupyInanimateCells(std::vector<navigate::Point>&);

public:
	static Arena* getArena();

	void settings();
	void shuffle();
	void occupy();
	void occupyCell(Point, Object*);

	bool foundWinner();
	string getWinner();

	string toString();

	~Arena();
};

#endif


