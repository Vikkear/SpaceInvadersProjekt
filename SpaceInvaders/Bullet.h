#pragma once
#include "GameEntities.h"
#include "Player.h"

class Bullet : public GameEntities {
private:
	int bulletType;
	bool isReadyToShoot = true;
public:
	Bullet();
	Bullet(int bulletType, int x, int y, float speed);
	~Bullet();

	int getBulletType();
	bool isReady();
	void toggleIsReady();

};