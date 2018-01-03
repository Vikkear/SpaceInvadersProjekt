#include "Bullet.h"
#include "GameEntities.h"

Bullet::Bullet() : GameEntities("bullet.png", 2000,2000, 0.1){

}

Bullet::Bullet(int bulletType, int x, int y, float speed) : GameEntities("bullet.png", x, y, speed){
	this->bulletType = bulletType;
}

Bullet::~Bullet() {

}

int Bullet::getBulletType() {
	return bulletType;
}

bool Bullet::isReady() {
	return isReadyToShoot;
}

void Bullet::toggleIsReady() {
	if (isReadyToShoot) {
		isReadyToShoot = false;
	}
	else {
		isReadyToShoot = true;
	}
}