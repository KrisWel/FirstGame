#pragma once
#include "Button.h"

class States
{
public:

	//Constructor & Destructor
	States(sf::RenderWindow* window, std::stack<States*>* states);
	virtual ~States();

	//Initializers
	void initializeFonts();
	void initializeMusic();

	//Functions
	const bool getQuit() const;
	virtual void updateMousePosition();
	sf::Vector2f getCenter();

	//Abstract functions
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void update(const float& dt) = 0;
	virtual void endState() = 0;

protected:

	//Variables
	sf::RenderWindow* window;
	bool endTopState;
	
	std::map<std::string, sf::Texture> texture;
	sf::Font font;
	std::stack<States*>* states;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::Music musicMain, musicStart;

private:
	
};

