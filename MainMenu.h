#pragma once
#include "States.h"
#include "Player.h"
#include "Ally.h"
#include "Enemy.h"
#include "Sword.h"
#include "Button.h"

class MainMenu : public States
{
public:

	//Constructor & Destructor
	MainMenu(sf::RenderWindow* window, std::stack<States*>* states, bool loadGame);
	~MainMenu();

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
	Ally* ally;
	Sword* sword;
	
	sf::Music music;

	bool stats;
	sf::Text statistics;
	std::string str;

	//Quest
	sf::RectangleShape backgroundQuest;
	bool quest;
	sf::Text questText;
	std::string strQ;
	bool spawn;

	//THE END
	sf::Text endText;
	std::string strEnd;
	sf::RectangleShape endShape;
	bool end;

	//Stats
	sf::RectangleShape background;
	sf::RectangleShape backgroundStats;
	float time;

	//PAUSE
	sf::RectangleShape backgroundPaused;
	sf::RectangleShape containerPaused;
	std::map<std::string, Button*>buttons;
	bool paused;

	sf::Texture backgroundTexture;
	sf::View view;
	
	//Enemy
	Enemy* enemy[5];
	int Enemydeads;
	int temp;

	//Collisions blocks
	sf::RectangleShape block[4];

	bool swords;
	

};

