#ifndef ARENA_H
#define ARENA_H

#include <navigate.h>
#include <object.h>
#include <cell.h>

using navigate::Dimensions;

class Arena {
private:
	Cell** cells;

	Arena();
	Arena(Dimensions);

	Arena(const Arena& copy);
	Arena& operator=(const Arena& copy);
	
public:
	static Arena* getArena();
	static Arena* getArena(Dimensions);

};
#endif

