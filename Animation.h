#pragma once
#include "Bibliotecs.h"

class Animation
{
public:

	//Constructor & Destructor
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	//Functions
	void update(int row, const float& dt, bool faceRight);

	//Variables
	sf::IntRect uvRect;

private:

	//Variables
	sf::Vector2u imageCount;
	sf::Vector2u currentimage;

	float totalTime;
	float switchTime;
};

