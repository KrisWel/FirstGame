#pragma once
#include "MainMenu.h"
#include "States.h"

class StartMenu : public States
{
public:

	//Constructor & Destructor
	StartMenu(sf::RenderWindow* window, std::stack<States*>* states);
	~StartMenu();

	//Initializors
	void initializeButtons();
	void initializeBackground();

	//Functions
	void render(sf::RenderTarget* target = nullptr);
	void update(const float& dt);
	void endState();

private:

	//Variables
	std::map<std::string, Button*>buttons;
	sf::RectangleShape button_background;
	bool resumebutton;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Music music;
	
};

