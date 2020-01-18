#pragma once
#include "Player.h"

class Collision
{
public:
	//Constructor & Destructor
	Collision(sf::RectangleShape body);
	~Collision();

	//Functions
	const bool checkCollsion(Collision other, float push);
	const sf::Vector2f getHalfSize();
	const sf::Vector2f getPosition();

	void move(float dx, float dy);

private:
	//Variables
	sf::RectangleShape body;
};

