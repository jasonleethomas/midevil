#ifndef CELL_H
#define CELL_H

#include <object.h>
#include <stdint.h>
#include <navigation.h>

using nav::Position;

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
