#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "GameEntities.h"
#include "GameClass.h"
#include <iostream>

GameClass::GameClass() {
	amountOfBullets = 6;
	int timeSinceLastFire = 0;
	currentBullet = 0;
	amountOfEnemies = 50;
	srand(time(0));

	if (!gameFont.loadFromFile("arial.ttf")) {
		
	}
	/*
	ammoText.setFont(gameFont);
	ammoText.setCharacterSize(30);
	ammoText.setColor(sf::Color::Red);
	ammoText.setPosition(sf::Vector2f(500, 500));
	ammoText.setString("Ammo: ");
	ammoText.setStyle(sf::Text::Bold); */
}


GameClass::~GameClass() {
	// förstör bullets
}

void GameClass::update(float dt) {
	
	// Lägger till fienderna i början av spelet
	if (!enemiesAreSpawned) {
		spawnEnemies();
		enemiesAreSpawned = true;
	}

	// Uppdaterar ammunitionen
	//ammoText.setString("Ammo: " + ammo);


	keepPlayerInsideWindow();

	// Input för spelarförflyttning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{		
		player.move(-0.2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(0.2, 0);
	}

	// Skjut
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->currentBullet++;
		if (this->currentBullet > 5) {
			this->currentBullet = 0;
		}
	}

	// Förflyttar skott utanför skärmen
	for (int i = 0; i < amountOfBullets; i++) {
		
		if (bullets[i].getYPosition() > 850 || bullets[i].getYPosition() < 0) {
			bullets[i].death();
			bullets[i].toggleIsReady();
			//ammo++;
		}
		
		
	}

	// Flyttar spelarns skott
	for (int i = 0; i < amountOfBullets; i++) {
		bullets[i].move(0, -0.1f);
	}

	// Flyttar fiendernas skott
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		enemyBullets[i].move(0, 0.1f);
	}

	// Håller koll på kollisionen mellan skotten och spelaren
	/*for (int i = 0; i < amountOfBullets; i++) {
		if (player.collidesWith(bullets[i])) {
			bullets[i].setPosition(2000, 2000);
		}
	}*/

	// Håller koll på kollision mellan skott och fiender
	for (int i = 0; i < amountOfEnemies; i++) {
		for (int j = 0; j < amountOfBullets; j++) {
			if (bullets[j].collidesWith(enemies[i])) {
				bullets[j].death();
				bullets[j].toggleIsReady();
				enemies[i].death();
				
				amountOfKills++;
				//ammo++;
			}
		}
	}
	
	// Flyttar fienderna
	moveEnemies();

	// Kollar om fiendernas skott hamnar utanför spelplanen
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		if (enemyBullets[i].getYPosition() > 800) {
			enemyBullets[i].death();
			enemyBullets[i].toggleIsReady();
			cout << "Utanfor";
		}

	}
	
	// Väljer en slumpmässig fiende och skjuter ifrån den fiendens position
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		int randNr = rand() % 40;

		if (enemyBullets[i].isReady()) {
			enemyBullets[i].fire(enemies[randNr], 25, 20);
			enemyBullets[i].toggleIsReady();
		}
	}

	// Kollar kollision mellan Fiendernas skott och Spelaren, blir spelaren träffad så ska spelaren tappa ett liv.
	// Den ska även kolla om spelaren dör.
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		if (enemyBullets[i].collidesWith(player)) {
			amountOfLives--;
			enemyBullets[i].death();
			enemyBullets[i].toggleIsReady();

			if (amountOfLives <= 0) {
				gameOver();
			}
		}
	}


}

void GameClass::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(player);
	//target.draw(ammoText);
	for (int i = 0; i < amountOfBullets; i++) {
		target.draw(bullets[i]);
	}

	for (int i = 0; i < amountOfEnemies; i++) {
		target.draw(enemies[i]);
	}

	for (int i = 0; i < amountOfEnemyBullets; i++) {
		target.draw(enemyBullets[i]);
	}

	
}

void GameClass::shoot(float speed) {
	bool isShot = false;

	for (int i = 0; i < amountOfBullets && !isShot; i++) {
		if (bullets[currentBullet].isReady()) {
			bullets[currentBullet].fire(player, 25, -20);
			bullets[currentBullet].toggleIsReady();
			isShot = true;
			ammo--;
		}
		else {
			currentBullet++;
		}
	}
	
	cout << "PEW";
}

void GameClass::keepPlayerInsideWindow() {
	
	if (player.getXPosition() < 0) {
		player.setXPosition(0);
	}

	if (player.getXPosition() > 1135) {
		player.setXPosition(1135);
	}
	

}

void GameClass::spawnEnemies() {
	bool enemiesAreSpawned = false;
	int x = 0;
	int y = 30;
	
	for (int i = 0; i < amountOfEnemies; i++) {
			
		enemies[i].setXPosition(x);
		enemies[i].setYPosition(y);
		
		x += 100;

		if (x >= 1100){
			x = 0;
			y += 100;
		}
		

	}
}

void GameClass::moveEnemies() {
	for (int i = 0; i < amountOfEnemies; i++) {
		if (enemies[i].getXPosition() > 1135) {
			enemies[i].setXPosition(0);
			enemies[i].setYPosition(enemies[i].getYPosition() + 100);
		}

		enemies[i].move(0.02f, 0);
	}
	
}

void GameClass::gameOver() {
	player.death();
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		enemyBullets[i].death();
	}

	for (int i = 0; i < amountOfEnemies; i++) {
		enemies[i].death();
	}

	for (int i = 0; i < amountOfBullets; i++) {
		bullets[i].death();
	}

}