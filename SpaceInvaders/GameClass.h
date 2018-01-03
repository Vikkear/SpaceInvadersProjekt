#pragma once
#include "GameEntities.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>

class GameClass : public sf::Drawable {
private:
	Player player;
	Bullet *bullets = new Bullet[6];
	Bullet *enemyBullets = new Bullet[6];
	Enemy *enemies = new Enemy[50];

	bool enemiesAreSpawned = false;

	int amountOfBullets;
	int timeSinceLastFire;
	int currentBullet;
	int amountOfEnemies;
	int amountOfKills = 0;
	int amountOfEnemyBullets = 6;
	int ammo = 6;

	int amountOfLives = 3;

	sf::Clock gameTime;
	sf::Font gameFont;
	sf::Text ammoText;

public:
	GameClass();
	~GameClass();

	void update(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void shoot(float speed);
	void keepPlayerInsideWindow();
	
	void spawnEnemies();

	void moveEnemies();

	void gameOver();

};