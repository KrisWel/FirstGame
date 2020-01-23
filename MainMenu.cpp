#include "MainMenu.h"

//										CONSTRUCTOR & DESTRUCTOR

MainMenu::MainMenu(sf::RenderWindow* window, std::stack<States*>* states, bool loadGame) 
	: States(window, states)
{
	this->window = window;
	this->view.setSize({ static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y) });
	this->initializeBackground();
	this->initializeTextures();
	musicMain.play();

	//ENTITY
	this->player = new Player(3800.f, 450.f, this->texture["Player"], sf::Vector2u(3, 3), 0.45f);
	this->ally = new Ally(3200.f, 2200.f, this->texture["Diego"]);
	
	this->enemy[0] = new Enemy(2220.f, 3425.f, this->texture["Enemy"]);
	this->enemy[1] = new Enemy(1910.f, 3535.f, this->texture["Enemy"]);
	this->enemy[2] = new Enemy(3660.f, 3475.f, this->texture["Enemy"]);
	this->enemy[3] = new Enemy(2530.f, 600.f, this->texture["Enemy"]);
	this->enemy[4] = new Enemy(5300.f, 3600.f, this->texture["Enemy"]);
	if (!swords)
		this->sword = new Sword(4600.f, 970.f, this->texture["Sword"]);

	for (int i = 0; i < 5; i++)
	{
		this->enemy[i]->setStats(30, 10, 10, 0, 20, 1);
	}

	//LOAD FROM FILE
	if (!loadGame)
	{
		this->player->setStats(100, 10, 10, 0, 20, 1);
		swords = false;
	}
	else
	{
		this->player->loadFromFile();
		if (this->player->ifSwordP)
			swords = true;
		swords = false;
	}

	//Text
	endText.setCharacterSize(100);
	endText.setFont(this->font);
	endText.setFillColor(sf::Color::Red);

	statistics.setCharacterSize(50);
	statistics.setFont(this->font);
	statistics.setFillColor(sf::Color::Red);
	str = "";

	questText.setCharacterSize(50);
	questText.setFont(this->font);
	questText.setFillColor(sf::Color::Red);


	//VARIABLES
	Enemydeads = 0;
	temp = 0;
	time = 0.f;

	//BOOLS
	this->stats = false;
	this->quest = false;
	this->spawn = false;
	this->paused = false;
	end = false;

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
	delete this->sword;
	delete this->ally;

	for (int i = 0; i < 5; i++)
		delete this->enemy[i];

	//deleting buttons
	auto it = this->buttons.begin();
	for (;it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//								INITIALIZERS

void MainMenu::initializeTextures()
{
	if (!this->texture["Player"].loadFromFile("graphics/sheet.png"))
		throw("TEXTURES ERROR");

	if (!this->texture["Diego"].loadFromFile("graphics/Diego.png"))
		throw("TEXTURES ERROR");
	if (!this->texture["Enemy"].loadFromFile("graphics/ork.png"))
		throw("TEXTURES ERROR");

	if (!this->texture["Sword"].loadFromFile("graphics/miecz.png"))
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

	//Background for pause
	this->backgroundPaused.setSize({ static_cast<float>(this->window->getSize().x),  static_cast<float>(this->window->getSize().y) });
	this->backgroundPaused.setFillColor(sf::Color(20, 20, 20, 100));
	this->containerPaused.setSize({ 
		static_cast<float>(this->window->getSize().x / 3.f),
		static_cast<float>(this->window->getSize().y / 2.f)});
	this->containerPaused.setFillColor(sf::Color(20, 20, 20, 200));

	//Background for Stats
	this->backgroundStats.setSize({ static_cast<float>(this->window->getSize().x / 3.f), static_cast<float>(this->window->getSize().y / 2.f) });
	this->backgroundStats.setFillColor(sf::Color(60, 60, 60, 200));

	//Background for Quest
	this->backgroundQuest.setSize({ static_cast<float>(this->window->getSize().x / 1.5f), static_cast<float>(this->window->getSize().y / 6.f) });
	this->backgroundQuest.setFillColor(sf::Color(60, 60, 60, 200));

	//END
	this->endShape.setSize({ static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y) });
	this->endShape.setFillColor(sf::Color(60, 60, 60, 255));
}

void MainMenu::initializeButtons()
{
	this->buttons["Resume"] = new Button(
		static_cast<float>(this->view.getCenter().x - 90.f),
		static_cast<float>(this->view.getCenter().y - 100.f),
		180.f, 40.f, 50, &this->font, "Resume Game",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
	this->buttons["Save"] = new Button(
		static_cast<float>(this->view.getCenter().x - 90.f),
		static_cast<float>(this->view.getCenter().y - 40.f),
		180.f, 40.f, 50, &this->font, "Save Game",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
	this->buttons["Exit"] = new Button(
		static_cast<float>(this->view.getCenter().x - 90.f),
		static_cast<float>(this->view.getCenter().y + 20.f),
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
	if (stats)
	{
		target->draw(this->backgroundStats);
		target->draw(this->statistics);
	}
	if (quest)
	{
		target->draw(this->backgroundQuest);
		target->draw(this->questText);
	}

	//rendering
	this->player->render(this->window);
	this->ally->render(this->window);
	if(!swords)
		this->sword->render(this->window);
	if(spawn)
		for (int i = 0; i < 5; i++)
			this->enemy[i]->render(this->window);

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

	if (end)
	{
		target->draw(this->endShape);
		target->draw(this->endText);
		auto its = this->buttons.find("Exit");
		if (its != this->buttons.end())
			its->second->render(target);
	}

	//POINTER
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(18);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}

void MainMenu::update(const float& dt)
{
	this->updateMousePosition();
	if (!end)
	{
		if (!paused)	//UNPAUSED*****************************************
		{
			
			this->player->update(dt);
			this->ally->update(dt);
			if (spawn)
				for (int i = 0; i < 5; i++)
					this->enemy[i]->update(dt);

			//Collision************************************
			//QUEST
			this->player->collision(this->ally->shape, dt);
			if (this->player->ifCollision)
			{
				this->quest = true;
				this->spawn = true;
			}


			//PICKING SWORD********************************
			if (!swords)
			{
				this->player->collision(this->sword->shape, dt);
				if (this->player->ifAttack && this->player->getImage() == 2 && this->player->ifCollision)
				{
					this->player->ifSwordP = true;
					this->sword->ifSwordS = true;
					this->sword->update(dt);
					this->player->setStats(
						this->player->getStats(1),
						this->player->getStats(2),
						this->player->getStats(3),
						this->player->getStats(4),
						this->player->getStats(5) + 30,
						this->player->getStats(6)
					);
				}
			}
			//PICKING SWORD********************************

			for (int i = 0; i < 4; i++)
			{
				this->player->collision(this->block[i], dt);
			}
			if (spawn)
			{
				for (int i = 0; i < 5; i++)//ATTACK ENEMY***************
				{
					this->player->collision(this->enemy[i]->shape, dt);
					if (this->player->ifAttack && this->player->getImage() == 2 && this->player->ifCollision)
						this->enemy[i]->getDMG(this->player->getStats(5) * this->player->getStats(2) * 0.1, dt);

					//player STATS***********************
					if (this->enemy[i]->getStats(1) <= 0)
					{
						Enemydeads++;
					}
				}
				if (Enemydeads >= 1 && Enemydeads > temp)
				{
					this->player->setStats(
						this->player->getStats(1) + 50,
						this->player->getStats(2) + 5,
						this->player->getStats(3) + 5,
						this->player->getStats(4) + 20,
						this->player->getStats(5),
						this->player->getStats(6) + 1
					);
				}
					//player STATS***********************
				temp = Enemydeads;
				if (Enemydeads < 5)
					Enemydeads = 0;
				else this->end = true;
			}

			this->view.setCenter(this->player->getPosition());
			this->window->setView(this->view);


			//updating keys******************************************************
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				if (!this->paused)
					this->pausedState();
				this->quest = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				time += dt;
				if (!stats && time >= 0.09f)
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
			//updating keys******************************************************
			//STATISTICS*************************************************************
			if (stats)
			{
				this->backgroundStats.setPosition(
					{
						static_cast<float>(this->view.getCenter().x) + static_cast<float>(this->window->getSize().x / 8.f),
						static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y / 3.f)
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
				this->statistics.setString(str);
				str = "";
				this->statistics.setPosition(
					{
						static_cast<float>(this->view.getCenter().x) + static_cast<float>(this->window->getSize().x) / 6.f,
						static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y) / 3.f
					});
			}//STATISTICS*************************************************************
			if (quest)
			{
				this->backgroundQuest.setPosition(
					{
						static_cast<float>(this->view.getCenter().x) - static_cast<float>(this->window->getSize().x / 4.f),
						static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y / 3.f)
					}
				);
				strQ = "ZABIJ 5 ORKOW ZAGRAZAJACY NASZEMU OBOZOWI !";
				this->questText.setString(strQ);
				this->questText.setPosition(
					{
						static_cast<float>(this->view.getCenter().x) - static_cast<float>(this->window->getSize().x) / 7.f,
						static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y) / 3.f
					});
			}
		}
		else	//PAUSED*********************************************
		{
			this->initializeButtons();
			this->backgroundPaused.setPosition(
				{
					static_cast<float>(this->view.getCenter().x) - static_cast<float>(this->window->getSize().x) / 2.f,
					static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y) / 2.f
				}
			);
			this->containerPaused.setPosition(
				{
					static_cast<float>(this->view.getCenter().x) - static_cast<float>(this->window->getSize().x) / 6.f,
					static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y) / 4.f
				}
			);

			//BUTTONS
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
				this->endTopState = true;
			}
		}
	}
	else // THIS IS THE END
	{
		this->initializeButtons();
		auto its = this->buttons.find("Exit");
		if (its != this->buttons.end())
			its->second->update(this->mousePosView);
		if (this->buttons["Exit"]->ifButtonPressed())
		{
			this->endTopState = true;
		}
		this->endShape.setPosition(
			{
				static_cast<float>(this->view.getCenter().x) - static_cast<float>(this->window->getSize().x) / 2.f,
				static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y) / 2.f
			}
		);
		strEnd = "THE END";
		endText.setString(strEnd);
		this->endText.setPosition(
			{
				static_cast<float>(this->view.getCenter().x) - static_cast<float>(this->window->getSize().x) / 10.f,
				static_cast<float>(this->view.getCenter().y) - static_cast<float>(this->window->getSize().y) / 2.f
			}
		);
	}
	//THE END
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

