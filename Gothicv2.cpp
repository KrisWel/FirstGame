#include "player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	//**************RENDEROWANIE OKIENKA***********************
	sf::RenderWindow window(sf::VideoMode(1300, 700), "Gothic", sf::Style::Default);
	//*********************************************************
	player bezi(1, { 100, 100 }, { 200, 200 });
	player diego(2, { 100, 100 }, { 100, 100 });
	player ork(3, { 100, 100 }, { 300, 300 });

	float deltatime = 0.0f;
	sf::Clock clock;

	//*************GLOWNA PETLA********************************
	while (window.isOpen())
	{
		deltatime = clock.restart().asSeconds();

		//***************PETLA EVENTOW*************************
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		//***********KONIEC PETLI EVENTOW******************

		bezi.moving(deltatime);
		window.clear(sf::Color(50, 150, 50));
		bezi.Draw(window);
		diego.Draw(window);
		ork.Draw(window);
		window.display();
	}
	//*****************KONIEC GLOWNEJ PETLI*******************
}
