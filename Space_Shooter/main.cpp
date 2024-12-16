#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	sf::CircleShape circle;
	window.setFramerateLimit(60);
	sf::Time time;
	sf::Clock clock;
	time = clock.getElapsedTime();
	while (window.isOpen())
	{
		window.clear();
		// process input 


		//update
		if (time.asSeconds() >= 1 / 60)
		{



			clock.restart();
		}


		//render
        
		window.display();

	}

}