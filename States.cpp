#include "States.h"

//										CONSTRUCTOR & DESTRUCTOR
States::States(sf::RenderWindow* window, std::stack<States*>* states)
{
	this->window = window; //Creating a new "window" for every state
	this->endTopState = false;
	this->states = states;
	this->initializeFonts();
	this->initializeMusic();
}

States::~States()
{
}

//								INITIALIZERS

void States::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/gothic.ttf"))
		std::cout << "Error font\n";
}

void States::initializeMusic()
{
	if (!this->musicMain.openFromFile("music/old_camp.ogg"))
		throw("Music Error");
	if (!this->musicStart.openFromFile("music/theme.ogg"))
		throw("Music Error");
	this->musicMain.setVolume(20);
	this->musicStart.setVolume(20);
}


//										FUNCTIONS
const bool States::getQuit() const
{
	return this->endTopState;
}

void States::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

sf::Vector2f States::getCenter()
{
	return sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}




