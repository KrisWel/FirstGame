#include "Animation.h"

//									CONSTRUCTOR & DESTRUCTOR

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	this->totalTime = 0.f;
	this->currentimage.x = 0;

	this->uvRect.width = texture->getSize().x / float(imageCount.x);
	this->uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

//								FUNCTIONS

void Animation::update(int row, const float& dt, bool faceRight)
{
	this->currentimage.y = row;
	this->totalTime += dt;

	//Changing the image
	if (this->totalTime >= this->switchTime)
	{
		this->totalTime -= this->switchTime;
		currentimage.x++;
		if (currentimage.x >= imageCount.x)
			currentimage.x = 0;
	}

	this->uvRect.top = this->currentimage.y * this->uvRect.height;

	//Changing side
	if (faceRight)
	{
		uvRect.left = currentimage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentimage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}
