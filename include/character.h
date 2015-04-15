#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdint.h>
#include <navigate.h>
#include <classify.h>
#include <object.h>

using navigate::Point;
using classify::Level;
using classify::Type;

class Character : public Object {
private:
	static int count;
	int xp;
	Level level;
	Type type;
			
	bool dead;

	int health;
	int damage;
	int range;
	int speed;

	int cost;

public:
	Character(Point, Level, Type);
	bool operator==(const Character&) const;

	Level getLevel() const;
	Type getType() const;

	virtual bool isDead() const;
 
	virtual int getHealth() const;
	virtual int getDamage() const;
	virtual int getRange() const;
	virtual int getSpeed() const;
	
	virtual bool isAnimate();
	virtual bool attack(Character*);	
	virtual void defend(Character*);

//	virtual bool reactTo(const Object*) = 0;
	virtual string toString() = 0;
};

#endif
