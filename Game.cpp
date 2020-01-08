#include "Game.h"

//								CONSTRUCTOR & DESTRUCTOR
Game::Game()
{
	initializeWindow();
	initializeStates();
}

Game::~Game()
{
	delete this->window;
	//if there is any state when game is closed destructor will delete these states
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
	std::cout << "End App\n";
}

//								INITIALIZERS
void Game::initializeWindow()
{
	//creating a window
	sf::ContextSettings window_settings;
	window_settings.antialiasingLevel = 0;

	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(),
		"PsuedoGothic", sf::Style::Fullscreen, window_settings);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initializeStates()
{
	//creating a states that will stacking
	this->states.push(new StartMenu(this->window, &this->states));
}

//								FUNCTIONS
void Game::update()
{
	this->dt = this->deltatime.restart().asSeconds();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt); //Calling a top state(stack) to update (States -> MainMenustate)
		if (this->states.top()->getQuit()) //ending state on top stack
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else //if there is no states window will close
	{
		this->window->close();
	}

	this->events();
}

void Game::render()
{
	this->window->clear();

	//rendering states
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::events()
{
	//Events loop
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::run()
{
	//Main loop
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}

}


