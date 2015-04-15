#include <player.h>
#include <classify.h>
#include <settings.h>

Player::Player(classify::User user) {
	this->user = user;
	this->team = playerSettings::getTeam(this->user);
	this->coin = playerSettings::getCoin(this->user);
}


