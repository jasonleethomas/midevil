#include <player.h>
#include <classify.h>
#include <settings.h>

using namespace playerSettings;

Player::Player(User user, Type team) {
	this->user = user;
	this->team = team;
	
	setTeam(this->user, this->team);
	
	this->coin = getCoin(this->user);
}


