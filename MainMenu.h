#pragma once
#include "States.h"
#include "Player.h"
#include "Button.h"

class MainMenu : public States
{
public:

	//Constructor & Destructor
	MainMenu(sf::RenderWindow* window, std::stack<States*>* states, bool loadGame);
	virtual ~MainMenu();

	//Initializors
	void initializeTextures();
	void initializeBackground();
	void initializeButtons();

	//Functions
	void render(sf::RenderTarget* target = nullptr);
	void update(const float& dt);
	void endState();
	void pausedState();
	void unpausedState();

private:

	//Variables
	Player* player;
	sf::Music music;
	bool stats;
	sf::RectangleShape background;
	sf::RectangleShape backgroundInventory;
	sf::RectangleShape backgroundPaused;
	sf::RectangleShape containerPaused;
	sf::Text statistics;
	std::map<std::string, Button*>buttons;
	sf::Texture backgroundTexture;
	sf::View view;
	bool paused;
	float time;
	std::string str;

	//Collisions blocks
	sf::RectangleShape block[4];

};

