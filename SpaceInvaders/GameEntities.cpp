#include "stdafx.h"
#include "GameEntities.h"
#include <SFML\Graphics.hpp>
#include <iostream>

GameEntities::GameEntities(string texturePath) {
	this->texturePath = texturePath;

	if (!texture.loadFromFile(texturePath)) {

	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(10, 720));
}

GameEntities::GameEntities() {
	texturePath = "enemy.png";
	if (!texture.loadFromFile(texturePath)) {

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

	}
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(x, y-20));

}

GameEntities::~GameEntities() {}

void GameEntities::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite);

}

void GameEntities::move(float x, float y) {
	this->x += x;
	this->y += y;

	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x + x, pos.y + y);

}

bool GameEntities::collidesWith(GameEntities &otherEntity) {
	bool isColliding = false;
	sf::FloatRect thisBoundingBox = sprite.getGlobalBounds();
	sf::FloatRect otherBoundingBox = otherEntity.sprite.getGlobalBounds();

	if (thisBoundingBox.intersects(otherBoundingBox)) {
		isColliding = true;
		cout << "Kollission!!!";
	}

	return isColliding;
}

void GameEntities::fire(GameEntities &otherEntity, int xOffset, int yOffset) {
	sf::Vector2f pos = sprite.getPosition();
	float otherPosX, otherPosY;

	otherPosX = otherEntity.getXPosition();
	otherPosY = otherEntity.getYPosition();

	sprite.setPosition(otherPosX+xOffset, otherPosY+yOffset);

}

float GameEntities::getXPosition() {
	float x;
	sf::Vector2f pos = sprite.getPosition();
	x = pos.x;
	
	return x;
}

float GameEntities::getYPosition() {
	float y;
	sf::Vector2f pos = sprite.getPosition();
	y = pos.y;
	
	return y;
}

void GameEntities::setXPosition(int position) {
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(position, pos.y);
}

void GameEntities::setYPosition(int position) {
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x, position);
}

void GameEntities::death() {
	setXPosition();
	setYPosition();
}