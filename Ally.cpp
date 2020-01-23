#include "Ally.h"

Ally::Ally(float x, float y, sf::Texture& texture)
{
	this->texture = texture;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition({ x, y });
	this->sprite.setOrigin({ 100.f, 56.5f });

	this->shape.setPosition({ x, y });
	this->shape.setSize({ static_cast<float>(this->texture.getSize().x), static_cast<float>(this->texture.getSize().y) });
	this->shape.setOrigin({ 100.f, 56.5f });
}

Ally::~Ally()
{
}

const int Ally::getStats(const int stat) const
{
	if (stat == 1) return this->hp;
	else if (stat == 2) return this->strength;
	else if (stat == 3) return this->dexterity;
	else if (stat == 4) return this->money;
	else if (stat == 5) return this->dmg;
	else if (stat == 6) return this->lvl;
	else return -1;
}

void Ally::update(const float& dt)
{
}


void Ally::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Ally::ifDead()
{
	if (this->hp <= 0)
		std::cout << "Dead\n";
}
