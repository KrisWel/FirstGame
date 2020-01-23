#pragma once
#include "Entity.h"


class Player : public Entity
{
public:

	//Constructor & Destructor
	Player(float x, float y, sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
	~Player();

	//Functions
	const int getStats(const int stat) const;
	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void ifDead();
	void setStats(int hp, 
		unsigned int strength, unsigned int dexterity, 
		unsigned int money, unsigned int dmg, unsigned int lvl);

	const sf::Vector2f getPosition() const;
	void collision(sf::RectangleShape& shape, const float& dt);

	void saveToFile();
	void loadFromFile();

	bool ifAttack;
	bool ifCollision;
	
	const int getImage() const;

	bool ifSwordP;
	bool tempSword;

private:

	//Variables
	sf::Vector2f movement;
	sf::Vector2f size;
	sf::RectangleShape body;

	Animation* animation;

	//friend class Collision;
};

