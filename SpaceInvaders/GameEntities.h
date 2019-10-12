#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;

class GameEntities : public sf::Transformable, public sf::Drawable{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float x;
	float y;
	double speed;
	string texturePath;

public:
	GameEntities(string texturePath);
	GameEntities();
	GameEntities(string texturePath, int x, int y, float speed);
	~GameEntities();

	void death(int xPos = 2000, int yPos = 2000);
	void fire(GameEntities &otherEntity, int xOffset, int yOffset);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void move(float x, float y);

	bool collidesWith(const GameEntities &otherEntity) const;
	
	float getXPosition() const;
	float getYPosition() const;

	void setXPosition(int position = 2000);
	void setYPosition(int position = 2000);
};
