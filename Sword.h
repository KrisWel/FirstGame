#pragma once
#include "Weapon.h"
class Sword : public Weapon
{
public:

	//Constructor & Destructor
	Sword(float x, float y, sf::Texture& texture);
	~Sword();

	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	sf::RectangleShape shape;
	bool ifSwordS;

private:

	//Variables
	

};

