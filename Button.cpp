#include "Button.h"

//										Constructor & Destructor

Button::Button(float x, float y, float width, float height,
	int size, sf::Font* font, std::string text, 
	sf::Color idlecolor, sf::Color hovercolor, sf::Color pressedcolor)
{
	this->shape.setSize({ width, height });
	this->shape.setPosition({ x, y });

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->size = size;
	this->text.setCharacterSize(this->size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y - (this->shape.getGlobalBounds().height / 4.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idlecolor = idlecolor;
	this->hovercolor = hovercolor;
	this->pressedcolor = pressedcolor;

	this->shape.setFillColor(this->idlecolor);

	this->buttonState = idle;
}

Button::~Button()
{
}


//											Functions

void Button::update(const sf::Vector2f mousPos)
{
	this->buttonState = idle;

	//checking if mouse is on the text
	if (this->shape.getGlobalBounds().contains(mousPos))
	{
		this->buttonState = hover;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = pressed;
	}

	switch (this->buttonState)
	{
	case idle:
		this->text.setFillColor(this->idlecolor);
		break;

	case hover:
		this->text.setFillColor(this->hovercolor);
		break;

	case pressed:
		this->text.setFillColor(this->pressedcolor);
		break;

	default:
		this->text.setFillColor(this->idlecolor);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	//drawing stuff
	target->draw(this->text);
}

const bool Button::ifButtonPressed() const
{
	if (this->buttonState == pressed)
		return true;

	return false;
}


