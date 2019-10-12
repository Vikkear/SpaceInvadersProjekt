#include "stdafx.h"
#include "GameEntities.h"
#include <SFML\Graphics.hpp>
#include <iostream>

GameEntities::GameEntities(string texturePath) {
	this->texturePath = texturePath;

	if (!texture.loadFromFile(texturePath)) {
		cout << "Couldnt load the texture!" << endl;
	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(10, 720));
}

GameEntities::GameEntities() {
	texturePath = "enemy.png";
	if (!texture.loadFromFile(texturePath)) {
		cout << "Couldnt load the texture!" << endl;
	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(10, 50));

}

GameEntities::GameEntities(string texturePath, int x, int y, float speed) {
	this->texturePath = texturePath;
	this->x = x;
	this->y = y;
	this->speed = speed;

	if (!texture.loadFromFile(texturePath)) {
		cout << "Couldnt load the texture!" << endl;
	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(x, y-20));

}

GameEntities::~GameEntities() {}

void GameEntities::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);

}

void GameEntities::move(float x, float y) {
	this->x = x;
	this->y = y;

	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x + x, pos.y + y);

}

// Funktion som kollar om GameEntityn kolliderar med en annan GameEntity
bool GameEntities::collidesWith(const GameEntities &otherEntity) const {
	bool isColliding = false;
	sf::FloatRect thisBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect otherBoundingBox = otherEntity.sprite.getGlobalBounds();

	if (thisBoundingBox.intersects(otherBoundingBox)) {
		isColliding = true;
	}

	return isColliding;
}

// Kallas ifrån game klassen, skjuter ut en GameEntity ifrån positionen
void GameEntities::fire(GameEntities &otherEntity, int xOffset, int yOffset) {
	sf::Vector2f pos = sprite.getPosition();
	float otherPosX, otherPosY;

	otherPosX = otherEntity.getXPosition();
	otherPosY = otherEntity.getYPosition();

	sprite.setPosition(otherPosX+xOffset, otherPosY+yOffset);

}

float GameEntities::getXPosition() const{
	float x;
	sf::Vector2f pos = sprite.getPosition();
	x = pos.x;
	
	return x;
}

float GameEntities::getYPosition() const{
	float y;
	sf::Vector2f pos = sprite.getPosition();
	y = pos.y;
	
	return y;
}

// Funktioner som används för att placera GameEntityn utanför spelplanen, används i death() funktionen
void GameEntities::setXPosition(int position) {
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(position, pos.y);
}

void GameEntities::setYPosition(int position) {
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x, position);
}


void GameEntities::death(int xPos, int yPos) {
	setXPosition(xPos);
	setYPosition(yPos);
}