#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string>

#include <navigate.h>
#include <classify.h>
#include <arena.h>
#include <cell.h>
#include <object.h>
#include <character.h>
#include <wizard.h>
#include <warrior.h>
#include <obstacle.h>

using std::vector;
using classify::Level;
using classify::Type;
using navigate::Point;
using navigate::maxBoundary;

namespace error {
	bool flag = false;
	string message;
}

void occupyArena(Cell***, Point);

int main() {

	Arena* arena = Arena::getArena(maxBoundary);
	
	arena->occupy();

	arena->shuffle();
	std::cout << arena->toString() << std::endl;

	delete arena;

	return 0;
}
