#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <navigate.h>
#include <object.h>
#include <cell.h>
#include <character.h>
#include <obstacle.h>

using navigate::Point;

class Arena {
private:	
	Point dimensions;
	Cell*** arena;

	std::vector<Character*> animateObjects;
	std::vector<Obstacle*> inanimateObjects;

	Arena();
	Arena(Point);

	Arena(const Arena& copy);
	Arena& operator=(const Arena& copy);
	
public:
	static Arena* getArena();
	static Arena* getArena(Point);

	void create();
	void destroy();
	void settings();
	void shuffle();
	string toString();
};
#endif


