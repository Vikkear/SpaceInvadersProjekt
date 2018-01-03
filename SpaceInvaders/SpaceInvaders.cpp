#include <SFML/Graphics.hpp>
#include "GameClass.h"
#include "Player.h"


int main() {


	GameClass spaceInvaders;
	sf::Clock gameTime;
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					spaceInvaders.shoot(0.1);
				}
			}

		}


		spaceInvaders.update(gameTime.restart().asSeconds());



		window.clear();
		window.draw(spaceInvaders);
		window.display();
	}



	return 0;
}