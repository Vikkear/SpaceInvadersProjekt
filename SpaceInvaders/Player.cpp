#include "Player.h"

Player::Player() : GameEntities("player.png") {
	this->amountOfLives = 3;
	this->score = 0;
}

Player::~Player() {
	// Vad ska h�nda n�r player f�rst�rs?

}

/*void Player::shoot() {
	// N�r man trycker p� blanksteg s� ska skott skjutas upp�t ifr�n spriten


}*/



bool Player::isAlive() {
	bool alive = false;
	
	if (this->amountOfLives > 0) {
		alive = true;
	}

	return alive;
}

int Player::getScore() {
	return score;
}