#include "Entity.h"

//								CONSTRUCTOR & DESTRUCTOR

Entity::Entity()
{
	this->initializeVariables();
}

Entity::~Entity()
{

}

//								INITIALIZORS

void Entity::initializeVariables()
{
	this->hp = 0;
	this->dexterity = 0;
	this->dmg = 0;
	this->money = 0;
	this->strength = 0;
	this->hp = 0;

}