#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture& texture)
{
	this->texture = texture;
	this->sprite.setPosition({ x, y });
	this->sprite.setOrigin({ 100.f, 56.5f });
	this->sprite.setTexture(this->texture);

	this->shape.setPosition({ x, y });
	this->shape.setOrigin({ 100.f, 56.5f });
	this->shape.setSize({ static_cast<float>(this->texture.getSize().x), static_cast<float>(this->texture.getSize().y) });

	deltatime = 0.f;
}

Enemy::~Enemy()
{
}

const sf::Vector2f Enemy::getposition()
{
	return this->sprite.getPosition();
}

const int Enemy::getStats(const int stat)
{
	if (stat == 1) return this->hp;
	else if (stat == 2) return this->strength;
	else if (stat == 3) return this->dexterity;
	else if (stat == 4) return this->money;
	else if (stat == 5) return this->dmg;
	else if (stat == 6) return this->lvl;
	else return -1;
}

void Enemy::update(const float& dt)
{
	ifDead();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Enemy::ifDead()
{
	if (this->hp <= 0)
	{
		//this->sprite.setColor(sf::Color::Transparent); 
		//this->shape.setSize({ 0.f, 0.f });
		if (!this->texture.loadFromFile("graphics/ork_dead.png"))
			throw("ERROR GRAPHICS");
		this->sprite.setTexture(this->texture);
	}
}

void Enemy::setStats(int hp,
	unsigned int strength, unsigned int dexterity,
	unsigned int money, unsigned int dmg, unsigned int lvl)
{
	this->hp = hp;
	this->strength = strength;
	this->dexterity = dexterity;
	this->money = money;
	this->dmg = dmg;
	this->lvl = lvl;
}

void Enemy::getDMG(int dmg, const float& dt)
{
	deltatime += dt;
	if (deltatime > 0.4f)
	{
		this->hp -= dmg;
		deltatime = 0.f;
	}
}


