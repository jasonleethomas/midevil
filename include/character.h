#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdint.h>
#include <navigate.h>
#include <classify.h>
#include <object.h>

using classify::Level;
using classify::Type;
using navigate::Position;

class Character : public Object {
private:
	Type type;
	Level level;

public:
	Character();
	Character(Position, Type, Level);

	virtual bool movedBy(Character*);
	virtual void moveTo(Position);
};

#endif
