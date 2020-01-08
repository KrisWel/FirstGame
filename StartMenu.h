#pragma once
#include "MainMenu.h"
#include "States.h"

class StartMenu : public States
{
public:

	//Constructor & Destructor
	StartMenu(sf::RenderWindow* window, std::stack<States*>* states);
	virtual ~StartMenu();

	//Initializors
	void initializeButtons();
	void initializeBackground();

	//Functions
	void render(sf::RenderTarget* target = nullptr);
	void update(const float& dt);
	void endState();

private:

	//Variables
	std::vector<sf::Texture> texutre;
	sf::RectangleShape background;
	sf::RectangleShape button_background;
	sf::Texture backgroundTexture;
	std::map<std::string, Button*>buttons;
	sf::Music music;
	
	bool resumebutton;

};

