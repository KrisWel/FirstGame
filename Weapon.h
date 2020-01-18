#pragma once
#include "Bibliotecs.h"
class Weapon
{
public:

	//Constructor & Destructor
	Weapon();
	virtual ~Weapon();

	//Functions
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

protected:

	//Variables
	sf::Texture texture;
	sf::Sprite sprite;
	int addDMG;

};

