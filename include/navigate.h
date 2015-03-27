#ifndef NAVIGATION_H
#define NAVIGATION_H

namespace navigate {
	struct Point {
		int x;
		int y;
	};
	
	const Point minBoundary = {3,3};
	const Point maxBoundary = {10,10};
}

#endif
