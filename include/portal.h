#ifndef PORTAL_H
#define PORTAL_H

#include <portal.h>
#include <obstacle.h>
#include <navigate.h>
#include <character.h>
#include <string>

class Portal : public Obstacle {
private:
public:
	Portal(navigate::Point);
	
	navigate::Point transport(Character*);
	std::string toString();
	
};
#endif
