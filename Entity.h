#pragma once
#include "Animation.h"

class Entity
{
public:
	//Constructor & Destructor
	Entity();
	virtual ~Entity();

	//Functions
	virtual const int getStats(const int stat) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
	virtual void ifDead() = 0;

protected:
	//Variables
	float movementSpeed;

	int hp;					//1
	unsigned int strength;	//2
	unsigned int dexterity;	//3
	unsigned int money;		//4
	unsigned int dmg;		//5
	unsigned int lvl;		//6

	sf::Sprite sprite;
	sf::Texture texture;

	Animation* animation;
	unsigned int row;
	bool faceRight;

private:

	//Initializors
	void initializeVariables();

};

