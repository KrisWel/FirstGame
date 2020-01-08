#pragma once
#include "Entity.h"


class Player : public Entity
{
public:
	Player(float x, float y, sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
	~Player();

	//Functions
	const int getStats(const int stat);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void ifDead();
	void setStats(int hp, 
		unsigned int strength, unsigned int dexterity, 
		unsigned int money, unsigned int dmg, unsigned int lvl);

	sf::Vector2f getPosition();
	void collision(sf::RectangleShape& shape, const float& dt);

	void saveToFile();
	void loadFromFile();

private:

	//Variables
	sf::Vector2f movement;
	sf::Vector2f size;
	sf::RectangleShape body;

	friend class Collision;
};

