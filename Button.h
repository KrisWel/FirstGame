#pragma once
#include "Bibliotecs.h"
enum button_states {idle = 0, hover, pressed};

class Button
{
public:

	//Constructor & Destructor
	Button(float x, float y, float width, float height,
		int size, sf::Font* font, std::string text,
		sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor);
	~Button();

	//Functions
	void update(const sf::Vector2f mousPos);
	void render(sf::RenderTarget* target);

	const bool ifButtonPressed() const;

private:

	//Variables
	sf::Font* font;
	sf::Color idlecolor;
	sf::Color hovercolor;
	sf::Color pressedcolor;
	sf::Text text;
	sf::RectangleShape shape;
	int size;

	short unsigned buttonState;

};

