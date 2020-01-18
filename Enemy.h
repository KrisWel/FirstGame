#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	
	//Constructor & Destructor
	Enemy(float x, float y, sf::Texture& texture);
	~Enemy();

	//Functions
	const sf::Vector2f getposition();
	const int getStats(const int stat);
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void ifDead();
	void setStats(int hp,
		unsigned int strength, unsigned int dexterity,
		unsigned int money, unsigned int dmg, unsigned int lvl);
	void getDMG(int dmg, const float& dt);


	sf::RectangleShape shape;

private:
	//Variables
	float deltatime;
};

