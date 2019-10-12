#include "Player.h"

Player::Player() : GameEntities("player.png") {
	this->amountOfLives = 3;
}

Player::~Player() {
	// Vad ska hända när player förstörs?

}

/*void Player::shoot() {
	// När man trycker på blanksteg så ska skott skjutas uppåt ifrån spriten


}*/



bool Player::isAlive() const{
	bool alive = false;
	
	if (this->amountOfLives > 0) {
		alive = true;
	}

	return alive;
}
