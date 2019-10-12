#include "Bullet.h"
#include "GameEntities.h"

Bullet::Bullet() : GameEntities("bullet.png", 2000,500, 0.1){

}

Bullet::Bullet(int x, int y, float speed) : GameEntities("bullet.png", x, y, speed){
	
}

Bullet::~Bullet() {

}



bool Bullet::isReady() const {
	return isReadyToShoot;
}

// Funktion som kallas varje g�ng man skjuter och varje g�ng man tr�ffar n�gonting
void Bullet::toggleIsReady() {
	if (isReadyToShoot) {
		isReadyToShoot = false;
	}
	else {
		isReadyToShoot = true;
	}
}