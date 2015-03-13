#include <navigate.h>
#include <object.h>
#include <obstacle.h>

Obstacle::Obstacle() : Object() {}

Obstacle::Obstacle(navigate::Point position) : Object(position) {}
