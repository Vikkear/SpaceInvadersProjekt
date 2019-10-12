#pragma once
#include "GameEntities.h"
#include "Player.h"

class Bullet : public GameEntities {
private:
	bool isReadyToShoot = true;
public:
	Bullet();
	Bullet(int x, int y, float speed);
	~Bullet();

	bool isReady() const;
	void toggleIsReady();

};