#include "StartMenu.h"

//									CONSTRUCOTR & DESTRUCTOR
StartMenu::StartMenu(sf::RenderWindow* window, std::stack<States*>* states) : States(window, states)
{
	this->window = window;

	this->initializeBackground();
	this->initializeButtons();

	musicStart.play();
}

StartMenu::~StartMenu()
{
	//Deleting all buttons
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//										INITIALIZORS

void StartMenu::initializeButtons()
{
	this->buttons["Menu_State"] = new Button(
		(background.getSize().x / 2.f) - 80.f, (background.getSize().y / 2.f) - 20.f,
		160.f, 50.f, 50, &this->font, "New Game",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
	this->buttons["Load"] = new Button(
		(background.getSize().x / 2.f) - 80.f, (background.getSize().y / 2.f)  + 40.f,
		160.f, 50.f, 50, &this->font, "Load Game",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
	this->buttons["Exit"] = new Button(
		(background.getSize().x / 2.f) - 80.f, (background.getSize().y / 2.f) + 100.f,
		160.f, 50.f, 50, &this->font, "Exit",
		sf::Color::Red, sf::Color::Blue, sf::Color::Cyan
	);
}

void StartMenu::initializeBackground()
{
	//init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile("graphics/background.jpg"))
	{
		std::cout << "ERROR!\n";
	}
	this->background.setTexture(&this->backgroundTexture);

	//init background for buttons
	this->button_background.setSize({ 570.f, 500.f });
	this->button_background.setPosition({ 400.f, 200.f });
	this->button_background.setFillColor(sf::Color(0, 0, 0, 150));

}

//										FUNCTIONS

void StartMenu::render(sf::RenderTarget* target)
{ 
	if (!target)
		target = this->window;

	//drawing all stuff
	target->draw(this->background);
	target->draw(this->button_background);

	//rendering all stuff
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void StartMenu::update(const float& dt)
{
	this->updateMousePosition();
	
	//updating buttons
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	if (this->buttons["Exit"]->ifButtonPressed())
	{
		this->endTopState = true;
	}
	if (this->buttons["Load"]->ifButtonPressed())
	{
		musicStart.pause();
		this->states->push(new MainMenu(this->window, this->states, true));
		this->endTopState = true;
	}
	if (this->buttons["Menu_State"]->ifButtonPressed())
	{
		musicStart.pause();
		this->states->push(new MainMenu(this->window, this->states, false));
		this->endTopState = true;
	}
}

void StartMenu::endState()
{
	std::cout << "End Start\n";
}



