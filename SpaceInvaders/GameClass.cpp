#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "GameEntities.h"
#include "GameClass.h"
#include <iostream>

GameClass::GameClass() {
	amountOfBullets = 2;
	currentBullet = 0;
	amountOfEnemies = 50;
	srand(time(0));

	if (!gameFont.loadFromFile("arial.ttf")) {
		cout << "Couldnt load the font!" << endl;
	}
	
	ammoText.setFont(gameFont);
	ammoText.setCharacterSize(20);
	ammoText.setFillColor(sf::Color(25, 125, 255));
	ammoText.setString("Ammo: 2");
	ammoText.setPosition(sf::Vector2f(1075, 750));
	
	gameOverText.setFont(gameFont);
	gameOverText.setCharacterSize(20);
	gameOverText.setFillColor(sf::Color::Blue);
	gameOverText.setPosition(sf::Vector2f(450, 350));

	lifeText.setFont(gameFont);
	lifeText.setCharacterSize(20);
	lifeText.setFillColor(sf::Color::Blue);
	lifeText.setString("Liv: " + to_string(amountOfLives));
	lifeText.setPosition(sf::Vector2f(50, 10));

	score.setFont(gameFont);
	score.setCharacterSize(20);
	score.setFillColor(sf::Color::Blue);
	score.setString("Score: 0");
	score.setPosition(sf::Vector2f(450, 10));
	
	timer.setFont(gameFont);
	timer.setCharacterSize(20);
	timer.setFillColor(sf::Color::Blue);
	timer.setString("Time: 0");
	timer.setPosition(sf::Vector2f(1000, 10));

	logicTimer.restart();
}


GameClass::~GameClass() {
	delete[] bullets;
	delete[] enemyBullets;
	delete[] enemies;
	delete[] asteroids;
}

void GameClass::update(float timeElapsedSinceLastLoop) {
	
	int timeElapsed = gameTime.getElapsedTime().asSeconds();
	
	logicTimer.restart();

	timer.setString("Time: " + to_string(timeElapsed));

	// Lägger till fienderna i början av spelet
	if (!enemiesAreSpawned) {
		spawnEnemies();
		spawnAsteroids();
		enemiesAreSpawned = true;
		gameTime.restart();
	}

	keepPlayerInsideWindow();

	//Kollar input
	checkInput(timeElapsedSinceLastLoop);

	// Förflyttar skott utanför skärmen
	for (int i = 0; i < amountOfBullets; i++) {
		if (bullets[i].getYPosition() > 850 || bullets[i].getYPosition() < 0) {
			bullets[i].death(2000, 500);
			bullets[i].toggleIsReady();	
			ammo++;
			ammoText.setString("Ammo: " + to_string(ammo));
		}
	}

	// Flyttar spelarns skott
	for (int i = 0; i < amountOfBullets; i++) {
		if (bullets[i].isReady() == false) {
			bullets[i].move(0, -0.0005 * timeElapsedSinceLastLoop);
		}
		
	}

	// Flyttar fiendernas skott
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		enemyBullets[i].move(0, 0.0005 * timeElapsedSinceLastLoop);
	}

	// Håller koll på kollision mellan skott och fiender
	for (int i = 0; i < amountOfEnemies; i++) {
		for (int j = 0; j < amountOfBullets; j++) {
			if (bullets[j].collidesWith(enemies[i])) {
				bullets[j].death(2000,500);
				bullets[j].toggleIsReady();
				enemies[i].death(2500,2500);
				scoreHandler.addToCurrentScore(100);
				score.setString("Score: " + to_string(scoreHandler.getScore()));
				amountOfKills++;
				
				if (amountOfKills >= 50) {
					if (!isGameOver) {
						gameOver();
					}
				}

				ammo++;
				ammoText.setString("Ammo: " + to_string(ammo));
			}
		}
	}
	
	// Flyttar fienderna
	moveEnemies(timeElapsedSinceLastLoop);

	// Kollar om fiendernas skott hamnar utanför spelplanen
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		if (enemyBullets[i].getYPosition() > 800) {
			enemyBullets[i].death();
			enemyBullets[i].toggleIsReady();
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
			lifeText.setString("Liv: " + to_string(amountOfLives));
			enemyBullets[i].death(1500,1500);
			enemyBullets[i].toggleIsReady();

			if (amountOfLives <= 0) {
				if (!isGameOver) {
					gameOver();
				}
			}
		}
	}

	// Kollar kollision mellan skott och asterioder
	for (int i = 0; i < amountOfBullets; i++) {
		for (int j = 0; j < 4; j++) {
			if (bullets[i].collidesWith(asteroids[j])) {
				asteroids[j].reSize();
				bullets[i].death(2000,500);
				bullets[i].toggleIsReady();
				ammo++;
				ammoText.setString("Ammo: " + to_string(ammo));
			}
		}
	}

	for (int i = 0; i < amountOfEnemyBullets; i++) {
		for (int j = 0; j < 4; j++) {
			if (enemyBullets[i].collidesWith(asteroids[j])) {
				asteroids[j].reSize();
				enemyBullets[i].death(1500,1500);
				enemyBullets[i].toggleIsReady();
			}
		}
	}

	// Kollar kollision mellan fienderna och asteroider
	for (int i = 0; i < amountOfEnemies; i++) {
		for (int j = 0; j < 4; j++) {
			if (enemies[i].collidesWith(asteroids[j])) {
				asteroids[j].death(3000,3000);
				enemies[i].death(2500, 2500);
			}
		}
	}

	for (int i = 0; i < amountOfEnemies; i++) {
		if (enemies[i].collidesWith(player)) {
			if (!isGameOver) {
				gameOver();
			}
		}
	}
	

 }

void GameClass::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(player);
	
	for (int i = 0; i < amountOfBullets; i++) {
		target.draw(bullets[i]);
	}

	for (int i = 0; i < amountOfEnemies; i++) {
		target.draw(enemies[i]);
	}

	for (int i = 0; i < amountOfEnemyBullets; i++) {
 		target.draw(enemyBullets[i]);
	}

	for (int i = 0; i < 4; i++) {
		target.draw(asteroids[i]);
	}
	
	target.draw(ammoText);
	target.draw(gameOverText);
	target.draw(lifeText);
	target.draw(score);
	target.draw(timer);
}

// Kallas när man trycker på skjut knappen, har man ammo tillgänglig så ska den skjutas
void GameClass::shoot(float speed) {
	bool isShot = false;
	if (ammo >= 1) {
		for (int i = 0; i < amountOfBullets && !isShot; i++) {
			if (bullets[currentBullet].isReady()) {
				bullets[currentBullet].fire(player, 25, -20);
				bullets[currentBullet++].toggleIsReady();
				isShot = true;
				ammo--;
				ammoText.setString("Ammo: " + to_string(ammo));
				currentBullet++;
			}
			else {
				currentBullet++;
			}
		}

		if (this->currentBullet > 1) {
			this->currentBullet = 0;
		}

	}
	
}

// Kallas varje frame för att hålla spelaren inuti fönstret
void GameClass::keepPlayerInsideWindow() {
	
	if (player.getXPosition() < 0) {
		player.setXPosition(0);
	}

	if (player.getXPosition() > 1135) {
		player.setXPosition(1135);
	}
	

}

// Lägger till alla asteroider i början av spelet
void GameClass::spawnAsteroids() {
	bool enemiesAreSpawned = false;
	int x = 175;
	

	for (int i = 0; i < 4; i++) {

		asteroids[i].setXPosition(x);
		asteroids[i].setYPosition(575);

		x += 250;
	}
}

// Lägger till alla fiender i början av spelet
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

// Kallas varje frame för att flytta fienderna, fienderna blir snabbare desto längre tid det har gått
void GameClass::moveEnemies(float timeElapsedSinceLastLoop) {
	for (int i = 0; i < amountOfEnemies; i++) {
		if (enemies[i].getXPosition() > 1135) {
			enemies[i].setXPosition(0);
			enemies[i].setYPosition(enemies[i].getYPosition() + 100);
		}

		float timeElapsed = gameTime.getElapsedTime().asSeconds();

		if (timeElapsed < 6) {
			enemies[i].move(0.00003 * timeElapsedSinceLastLoop, 0);
		}
		else if (timeElapsed >= 6 && timeElapsed < 12)  {
			enemies[i].move(0.00010 * timeElapsedSinceLastLoop, 0);
		}
		else if( timeElapsed >= 12 && timeElapsed < 18) {
			enemies[i].move(0.00020 * timeElapsedSinceLastLoop, 0);
		}
		else {
			enemies[i].move(0.00035 * timeElapsedSinceLastLoop, 0);
		}
		
	}
	
}

// Kallas antingen när man dör eller när man har dödat alla fiender.
// Beroende på vilket av de två alternativen så skrivs det ut en text på mitten
// av skärmen och spelet kollar igenom om man har lyckats få en highscore eller inte.
// Har man lyckats få en highscore så får man skriva in sitt namn i konsolen och så
// skrivs det namnet in i highscore listan som sedan skrivs ut i konsolen.
void GameClass::gameOver() {
	isGameOver = true;
	lifeText.setString("Liv: 0");
	ammoText.setString("Ammo: 0");
	player.death();
	for (int i = 0; i < amountOfEnemyBullets; i++) {
		enemyBullets[i].death();
	}

	for (int i = 0; i < amountOfEnemies; i++) {
		enemies[i].death(2500,2500);
	}

	for (int i = 0; i < amountOfBullets; i++) {
		bullets[i].death();
	}

	for (int i = 0; i < 4; i++) {
		asteroids[i].death(3000, 3000);
	}

	if (amountOfKills >= 50) {
		gameOverText.setString("Bra jobbat! Du vann!");
	}
	else {
		gameOverText.setString("Dåligt jobbat! Du förlorade!");
	}

	int timeElapsed = gameTime.getElapsedTime().asSeconds();

	scoreHandler.addToCurrentScore(scoreHandler.getScore() / timeElapsed);

	scoreHandler.loadScoreFromFile();
	scoreHandler.checkIfHighscore();
	scoreHandler.saveScoreToFile();
}

void GameClass::checkInput(float timeElapsed) {
	
	// Input för spelarförflyttning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-0.0002 * timeElapsed , 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(0.0002 * timeElapsed, 0);
	}

}