#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <navigate.h>
#include <object.h>

class Obstacle : public Object {
public:
	Obstacle();
	Obstacle(navigate::Point);

	virtual bool movedBy(Object*);
	virtual bool reactTo(Object*);
	virtual char display();

	virtual ~Obstacle() {}
};
#endif

