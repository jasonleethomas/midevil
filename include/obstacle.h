#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <navigate.h>
#include <string>
#include <object.h>

class Obstacle : public Object {
public:
	Obstacle(navigate::Point);

	bool isAnimate();
	std::string toString();

	virtual ~Obstacle() {}
};
#endif

