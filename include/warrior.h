#ifndef WARRIOR_H
#define WARRIOR_H

class Warrior : public Character {
public:
	Warrior();
	Warrior(Point);
	
	string toString();
};

#endif
