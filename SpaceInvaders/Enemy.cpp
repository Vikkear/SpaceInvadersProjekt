#include "Enemy.h"
#include "GameEntities.h"

Enemy::Enemy() : GameEntities("enemy.png") {

}

Enemy::Enemy(int x, int y, float speed) : GameEntities ("enemy.png",x,y,speed){
	
}

Enemy::~Enemy() {

}

void Enemy::shoot() {

}

