#pragma once
#include "GameEntities.h"	


class Asteroid : public GameEntities {
private:
	int size;

public:
	Asteroid();
	~Asteroid();

	void reSize();
};