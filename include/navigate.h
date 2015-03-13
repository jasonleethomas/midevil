#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <stdint.h>

namespace navigate {

	enum Boundaries {MIN_AREA = 9, MAX_AREA = 100, DEF_AREA = 100};

	struct Dimensions {
		uint8_t x;
		uint8_t y;
	};

	struct Position {
		uint8_t x;
		uint8_t y;	
		uint8_t z;
	};
}

#endif
