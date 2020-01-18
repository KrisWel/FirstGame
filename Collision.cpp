#include "Collision.h"

Collision::Collision(sf::RectangleShape body) : body(body)
{
}

Collision::~Collision()
{
}

const bool Collision::checkCollsion(Collision other, float push)
{
	sf::Vector2f otherPosition = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float crossX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float crossY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (crossX < 0.f && crossY < 0.f)
	{
		push = std::min(std::max(push, 0.f), 1.f);

		if (crossX > crossY)
		{
			if (deltaX > 0.f)
			{
				move(crossX * (1.f - push), 0.f);
				other.move(-crossX * push, 0.f);
			}
			else
			{
				move(-crossX * (1.f - push), 0.f);
				other.move(crossX * push, 0.f);
			}
		}
		else
		{
			if (deltaY > 0.f)
			{
				move(0.f, crossY * (1.f - push));
				other.move(0.f, -crossY * push);
			}
			else
			{
				move(0.f, -crossY * (1.f - push));
				other.move(0.f, crossY * push);
			}
		}
	}

	return false;
}

const sf::Vector2f Collision::getHalfSize()
{
	sf::Vector2f size;
	size.x = (float)body.getSize().x / 2.f;
	size.y = (float)body.getSize().y / 2.f;
	return size;
}

const sf::Vector2f Collision::getPosition()
{
	return body.getPosition();
}

void Collision::move(float dx, float dy)
{
	this->body.move({ dx, dy });
}
