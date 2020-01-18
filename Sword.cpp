#include "Sword.h"

Sword::Sword(float x, float y, sf::Texture& texture)
{
	this->texture = texture;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition({ x, y });

	this->shape.setSize({ static_cast<float>(this->texture.getSize().x), static_cast<float>(this->texture.getSize().y) });
	this->shape.setPosition({ x, y });

	this->ifSwordS = false;
}

Sword::~Sword()
{
}

void Sword::update(const float& dt)
{
	if (ifSwordS)
	{
		this->sprite.setScale({ 0.f, 0.f });
		this->sprite.setPosition({ -100.f, -100.f });
		this->shape.setScale({ 0.f, 0.f });
		this->shape.setPosition({ -100.f, -100.f });
	}
	ifSwordS = false;
}

void Sword::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}