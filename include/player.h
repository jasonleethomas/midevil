#ifndef PLAYER_H
#define PLAYER_H

#include <classify.h>

using classify::Type;
using classify::User;

class Player {
private:
	User user;
	Type team;

	int coin;
	
public:
	Player(User, Type);
	
	void pickTeam();	
};

#endif
