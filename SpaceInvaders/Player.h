#pragma once
#include "GameEntities.h"

class Player : public GameEntities {
private:
	int amountOfLives;
	int score;
public:
	Player();
	~Player();
	
	bool isAlive() const;
};