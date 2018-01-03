#pragma once
#include "GameEntities.h"

class Enemy : public GameEntities{
private:


public:
	Enemy();
	Enemy(int x, int y, float speed);
	~Enemy();

	void shoot();
};