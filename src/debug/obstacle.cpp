#include <navigate.h>
#include <object.h>
#include <obstacle.h>

Obstacle::Obstacle() : Object() {}

Obstacle::Obstacle(navigate::Position position) : Object(position) {}
