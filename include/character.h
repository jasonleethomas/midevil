#ifndef CHARACTER_H
#define CHARACTER_H

#include <object.h>
#include <cell.h>
#include <stdint.h>

class Character : public Object {
private:
	static uint16_t count = 0;

	uint16_t cost;
	uint16_t health;
	uint16_t speed;
	uint16_t damage;
	uint16_t range;

public:
	bool attack();
	bool defend();
	bool move();
};
#endif
