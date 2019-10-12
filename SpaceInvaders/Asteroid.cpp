#include "Asteroid.h"

Asteroid::Asteroid() : GameEntities("asteroids.png", 0, 0, 0){
	this->size = 100;

}

Asteroid::~Asteroid() {


}


void Asteroid::reSize() {
	this->size *= 0.75;

	if (size <= 10){
		death(3000,3000);
	}
}
