#pragma once
#include "StartMenu.h"

class Game
{
public:

	//Constructor & Destructor
	Game();
	~Game();

	//Functions
	void run();
	void update();
	void render();
	void events();
	
	//Initializers
	void initializeStates();
	void initializeWindow();

private:

	//Variables
	sf::RenderWindow* window;
	sf::Clock deltatime;
	sf::Event event;
	std::stack<States*> states;

	float dt;
};

