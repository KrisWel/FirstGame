#include "MainMenu.h"

//										CONSTRUCTOR & DESTRUCTOR

MainMenu::MainMenu(sf::RenderWindow* window, std::stack<States*>* states, bool loadGame) 
	: States(window, states)
{
	this->window = window;
	this->initializeBackground();
	this->initializeTextures();
	this->player = new Player(3800.f, 450.f, this->texture["Player_idle"], sf::Vector2u(3, 3), 0.45f);
	if (!loadGame)
	{
		this->player->setStats(100, 10, 10, 0, 20, 1);
	}
	else
	{
		this->player->loadFromFile();
	}
	this->stats = false;
	this->paused = false;
	this->view.setSize({ (float)this->window->getSize().x, (float)this->window->getSize().y });
	
	musicMain.play();
	time = 0.f;

	statistics.setCharacterSize(50);
	statistics.setFont(this->font);
	statistics.setFillColor(sf::Color::Red);
	str = "";

	//Collision blocks
	for (int i = 0; i < 4; i++)
	{
		switch(i)
		{
		case 0:
			block[i].setPosition({ 0.f, -1.f });
			block[i].setSize({ 7000.f, 1.f });
			break;
		case 1:
			block[i].setPosition({ 0.f, 5000.f });
			block[i].setSize({ 7000.f, 1.f });
			break;
		case 2:
			block[i].setPosition({ -1.f, 0.f });
			block[i].setSize({ 1.f, 5000.f });
			break;
		case 3:
			block[i].setPosition({ 7000.f, 0.f });
			block[i].setSize({ 1.f, 5000.f });
			break;
		}
		block[i].setFillColor(sf::Color(0, 0, 0, 0));
	}
}

MainMenu::~MainMenu()
{
	delete this->player;
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//								INITIALIZERS

void MainMenu::initializeTextures()
{
	if (!this->texture["Player_idle"].loadFromFile("graphics/sheet.png"))
		throw("TEXTURES ERROR");
}

void MainMenu::initializeBackground()
{
	//init background
	this->background.setSize({ 7000.f, 5000.f });
	if (!this->backgroundTexture.loadFromFile("graphics/background2.jpg"))
	{
		std::cout << "ERROR!\n";
	}
	this->background.setTexture(&this->backgroundTexture);

	this->backgroundPaused.setSize({ (float)this->window->getSize().x,  (float)this->window->getSize().y });
	this->backgroundPaused.setFillColor(sf::Color(20, 20, 20, 100));

	this->containerPaused.setSize({ 
		(float)this->window->getSize().x / 3.f, 
		(float)this->window->getSize().y / 2.f});
	this->containerPaused.setFillColor(sf::Color(20, 20, 20, 200));

	this->backgroundInventory.setSize({ (float)this->window->getSize().x / 3.f, (float)this->window->getSize().y / 2.f });
	this->backgroundInventory.setFillColor(sf::Color(60, 60, 60, 200));
}

void MainMenu::initializeButtons()
{
	this->buttons["Resume"] = new Button(
		(float)this->view.getCenter().x - 90.f,
		(float)this->view.getCenter().y - 100.f,
		180.f, 40.f, 50, &this->font, "Resume Game",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
	this->buttons["Save"] = new Button(
		(float)this->view.getCenter().x - 90.f,
		(float)this->view.getCenter().y - 40.f,
		180.f, 40.f, 50, &this->font, "Save Game",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
	this->buttons["Exit"] = new Button(
		(float)this->view.getCenter().x - 90.f,
		(float)this->view.getCenter().y + 20.f,
		180.f, 40.f, 50, &this->font, "Exit",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
}

//									FUNCTIONS

void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	//drawing all stuff
	target->draw(this->background);
	for(int i=0; i<4; i++)
		target->draw(block[i]);
	this->player->render(this->window);

	if (stats)
	{
		target->draw(this->backgroundInventory);
		target->draw(this->statistics);
	}

	//PAUSED
	if (this->paused)
	{
		target->draw(this->backgroundPaused);
		target->draw(this->containerPaused);
		for (auto& it : this->buttons)
		{
			it.second->render(target);
		}
	}
	
}

void MainMenu::update(const float& dt)
{
	if (!paused)	//UNPAUSED
	{
		this->updateMousePosition();
		this->player->update(dt);

		//Collision
		for(int i =0; i<4; i++)
			this->player->collision(this->block[i], dt);


		this->view.setCenter(this->player->getPosition());
		this->window->setView(this->view);


		//updating keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!this->paused)
				this->pausedState();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			time += dt;
			if (!stats && time >=0.09f)
			{
				stats = true;
				time = 0.f;
			}
			else if (stats && time >= 0.09f)
			{
				stats = false;
				time = 0.f;
			}
			
		}
		if (stats)
		{
			this->backgroundInventory.setPosition(
				{
					(float)this->view.getCenter().x + (float)this->window->getSize().x / 8.f,
					(float)this->view.getCenter().y - (float)this->window->getSize().y / 3.f
				}
			);
			for (int i = 1; i <= 6; i++)
			{
				int tmp = this->player->getStats(i);
				switch (i)
				{
				case 1:
					str += "HP: ";
					break;
				case 2:
					str += "Strength: ";
					break;
				case 3:
					str += "Dexterity: ";
					break;
				case 4:
					str += "Money: ";
					break;
				case 5:
					str += "DMG: ";
					break;
				case 6:
					str += "LVL: ";
					break;
				}
				str += std::to_string(tmp);
				str += "\n";
			}
			//std::cout << str;
			this->statistics.setString(str);
			str = "";
			this->statistics.setPosition(
				{
					(float)this->view.getCenter().x + (float)this->window->getSize().x / 6.f,
					(float)this->view.getCenter().y - (float)this->window->getSize().y / 3.f
				});
		}
		
	}
	else	//PAUSED
	{
		this->initializeButtons();
		this->updateMousePosition();
		this->backgroundPaused.setPosition(
			{ 
				(float)this->view.getCenter().x - (float)this->window->getSize().x / 2.f,
				(float)this->view.getCenter().y - (float)this->window->getSize().y / 2.f
			}
		);
		this->containerPaused.setPosition(
			{
				(float)this->view.getCenter().x - (float)this->window->getSize().x / 6.f,
				(float)this->view.getCenter().y - (float)this->window->getSize().y / 4.f
			}
		);
		for (auto& it : this->buttons)
		{
			it.second->update(this->mousePosView);
		}
		if (this->buttons["Resume"]->ifButtonPressed())
		{
			if (this->paused)
				this->unpausedState();
		}
		if (this->buttons["Save"]->ifButtonPressed())
		{
			this->player->saveToFile();
		}
		if (this->buttons["Exit"]->ifButtonPressed())
		{
			this -> endTopState = true;
		}
	}

}

void MainMenu::endState()
{
	std::cout << "End MainMenu\n";
}

void MainMenu::pausedState()
{
	this->paused = true;
}

void MainMenu::unpausedState()
{
	this->paused = false;
}

