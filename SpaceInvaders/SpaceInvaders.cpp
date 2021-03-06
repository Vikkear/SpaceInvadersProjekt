#include <SFML/Graphics.hpp>
#include "GameClass.h"
#include "Player.h"


int main() {


	GameClass spaceInvaders;
	sf::Clock gameTime;
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
	// Bestämde mig för att sätta Framelimiten på 60 för att logiken ska fungera för de flesta datorer, försökte först 
	// Använda mig utav en FPS räknare men fick det inte att fungera
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
 		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// När man klickar på space så ska man skjuta inuti spelet
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					spaceInvaders.shoot(0.1);
				}
			}

		}


		spaceInvaders.update(gameTime.getElapsedTime().asMicroseconds());
		gameTime.restart();


		window.clear();
		window.draw(spaceInvaders);
		window.display();
	}



	return 0;
}