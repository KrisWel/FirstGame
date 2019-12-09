#pragma once
#include <SFML/Graphics.hpp>

class Weapon
{
public:
	Weapon();
	void Draw(sf::RenderWindow& window);
	void SetPosit(sf::Vector2f posit);
	void scale(float a, sf::Vector2f b);
private:
	sf::RectangleShape mass;
	sf::Texture texture;
};

class player
{
public:
	player(int nr, sf::Vector2f size, sf::Vector2f posit);
	void Draw(sf::RenderWindow& window);
	void moving(float deltatime);
	sf::Vector2f body_posit;
private:
	sf::RectangleShape body;
	sf::Texture texture;
	bool right=true;
	float totaltime = 0.0f;
	Weapon weapon;
};

