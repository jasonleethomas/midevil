#include <player.h>
#include <classify.h>
#include <settings.h>

using namespace playerSettings;

Player::Player(classify::User user, classify::Type team) {
	this->user = user;
	this->team = team;
	
	setTeam(this->user, this->team);
	
	this->coin = getCoin(this->user);
}


