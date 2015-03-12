#ifndef CELL_H
#define CELL_H

#include <object.h>
#include <stdint.h>
typedef struct {
	uint8_t x;
	uint8_t y;
}	Position;

typedef struct {
	uint8_t xdim;
	uint8_t ydim;
} Dimensions;

class Cell {
private:
	bool vacancy;

	Position position;
	Dimensions dimensions;
	Object* occupant;

public:
	Cell();	
	Cell(Position);
	Cell(Position, Object*);

	Position getPosition() const;
	Dimensions getDimensions() const;
	Object* getOccupant() const;

	bool isVacant() const;
	bool occupy(Object*);
	bool vacate();

};
#endif
