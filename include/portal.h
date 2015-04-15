#ifndef PORTAL_H
#define PORTAL_H

#include <cell.h>
#include <arena.h>
#include <navigate.h>
#include <object.h>

class Portal : public Cell {
public:
	Portal(navigate::Point);
	Portal(navigate::Point, Object*);
	
	void transportOccupant(Arena*);	
	
	bool isAnimate();
	std::string toString();
};

#endif