#include "player.h"

void Player::update() {
}

int Player::getScore() {
	return score;
}
void Player::setScore(int s) {
	score = s;
}

int Player::getHealth() {
	return health;
}

void Player::setHealth(int h) {
	health = h;
}

void Player::increaseScore(int s) {
	score += s;
}

void Player::decreaseHealth(int h) {
	health -= h;
}