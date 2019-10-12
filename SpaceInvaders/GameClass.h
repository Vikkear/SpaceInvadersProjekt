#pragma once
#include "GameEntities.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Score.h"
#include <vector>

class GameClass : public sf::Drawable {
private:
	Player player;
	Bullet *bullets = new Bullet[2];
	Bullet *enemyBullets = new Bullet[6];
	Enemy *enemies = new Enemy[50];
	Asteroid *asteroids = new Asteroid[4];

	Score scoreHandler;

	bool enemiesAreSpawned = false;	// bool som används i början av spelet för att skapa alla fiender/asteroider
	bool isGameOver = false;	// bool som ser till att gameOver() funktionen inte kallas mer än en gång

	int amountOfBullets;
	int currentBullet;
	int amountOfEnemies;
	int amountOfKills = 0;
	int amountOfEnemyBullets = 6;
	int ammo = 2;
	int amountOfLives = 3;

	sf::Clock clock; 
	sf::Clock gameTime;
	sf::Clock logicTimer;
	
	sf::Font gameFont;
	
	sf::Text ammoText;
	sf::Text gameOverText;
	sf::Text score;
	sf::Text lifeText;
	sf::Text timer;


public:
	GameClass();
	~GameClass();

	void update(float timeElapsedSinceLastLoop);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void shoot(float speed);
	void keepPlayerInsideWindow();
	
	void spawnAsteroids();
	void spawnEnemies();
	void moveEnemies(float timeElapsed);
	void gameOver();
	
	void checkInput(float timeElapsed);
	

};