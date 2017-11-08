//
// I made this program to research the use of blendmode
//

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include <queue>
#include <iostream>
#include "Object.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 500), "Blend test");
	window.setFramerateLimit(360);
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Event event;
	int blendMode{ 0 };

	// Initialize values
	std::vector<Object> objects;
	std::queue<sf::BlendMode> blendModes;
	blendModes.push(sf::BlendAdd);
	blendModes.push(sf::BlendMultiply);
	blendModes.push(sf::BlendNone);

	for (int i = 0; i < 3; ++i)
	{
		objects.push_back(Object(100 + 200 * i, 200, 100, 100, blendModes.front()));
		blendModes.pop();
	}
	objects.push_back(Object(325, 400, 50, 50, sf::BlendAdd));
	objects.back().setBlendMode(sf::BlendAdd);
	objects.back().setColor(sf::Color::Green);

	clock.restart();
	elapsedTime = clock.restart();

	while (window.isOpen())
	{
		elapsedTime = clock.restart();
		if (elapsedTime.asSeconds() > 1.f)
			elapsedTime = sf::Time(sf::milliseconds(1000/360));
		
		while (window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				++blendMode %= 3;
				std::cout << blendMode << '\n';
				switch (blendMode)
				{
				case 0:
					objects.back().setBlendMode(sf::BlendAdd);
					break;
				case 1:
					objects.back().setBlendMode(sf::BlendMultiply);
					break;
				case 2:
					objects.back().setBlendMode(sf::BlendNone);
					break;
				}
				break;

			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			window.close();

		//objects.back().setPosition(sf::Vector2f(0, 0));
		objects.back().setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window),window.getDefaultView()));

		// Draw
		sf::RectangleShape dark;
		dark.setSize(sf::Vector2f(1000, 1000));
		dark.setPosition(0, 0);
		dark.setFillColor(sf::Color(0,0,0, 200));
		window.clear(sf::Color::Cyan);
		window.draw(dark);
		for (const auto &iter : objects)
			window.draw(iter);
		window.display();
	}

	return 0;
}