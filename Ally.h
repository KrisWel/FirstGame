#pragma once
#include "Entity.h"
class Ally : public Entity
{
public:

	//Constructor & Destructor
	Ally(float x, float y, sf::Texture& texture);
	~Ally();

	//Functions
	const int getStats(const int stat);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void ifDead();

	//Variables
	sf::RectangleShape shape;

private:

};

