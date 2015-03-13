#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <navigate.h>
#include <object.h>

class Obstacle : public Object {
public:
	Obstacle();
	Obstacle(navigate::Position);
};
#endif

