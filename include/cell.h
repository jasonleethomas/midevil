#ifndef CELL_H
#define CELL_H

#include <stdint.h>
#include <navigate.h>
#include <object.h>

using navigate::Position;

class Cell {
private:
	bool vacancy;

	Position position;
	Object* occupant;

public:
	Cell();	
	Cell(Position);
	Cell(Position, Object*);

	Position getPosition() const;
	Object* getOccupant() const;

	bool isVacant() const;
	bool occupy(Object*);
	bool vacate();
};
#endif
