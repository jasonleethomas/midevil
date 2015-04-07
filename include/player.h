#ifndef PLAYER_H
#define PLAYER_H

#include <classify.h>

class Player {
private:
	classify::User user;
	classify::Type team;
	int coin;
	
public:
	Player(classify::User);
};

#endif
