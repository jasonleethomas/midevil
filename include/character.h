#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdint.h>
#include <navigate.h>
#include <classify.h>
#include <object.h>

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
	Character(Level, Type);

	Level getLevel() const;
	Type getType() const;

	bool isDead() const;
 
	int getHealth() const;
	int getDamage() const;
	int getRange() const;
	int getSpeed() const;
	
	bool fights();
	bool attack(Character*);	
	void defend(Character*);

	virtual bool reactTo(const Object*) = 0;
	virtual string toString() = 0;
};

#endif
