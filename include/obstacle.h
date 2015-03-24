#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <navigate.h>
#include <string>
#include <object.h>

class Obstacle : public Object {
public:
	Obstacle(navigate::Point);

	bool fights();
	std::string toString();

	virtual ~Obstacle() {}
};
#endif

