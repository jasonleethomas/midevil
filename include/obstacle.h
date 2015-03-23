#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <navigate.h>
#include <string>
#include <object.h>

class Obstacle : public Object {
public:
	Obstacle();

	bool fights();
	std::string toString();

	virtual ~Obstacle() {}
};
#endif

