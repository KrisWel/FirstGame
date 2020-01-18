#include "Player.h"

//									CONSTRUCTOR & DESTRUCTOR

Player::Player(float x, float y, sf::Texture& texture, sf::Vector2u imageCount, float switchTime)
{
	this->texture = texture;
	this->sprite.setPosition(x, y);
	this->sprite.setOrigin({ 100.f, 56.5f });

	this->row = 0;
	this->faceRight = true;
	this->movementSpeed = 1000.f;
	this->ifAttack = false;
	this->ifCollision = false;
	
	this->animation = new Animation(&this->texture, imageCount, switchTime);

	this->ifSwordP = false;
	tempSword = false;
}

Player::~Player()
{
	delete this->animation;
}

//									FUNCTIONS

sf::Vector2f Player::getPosition()
{
	return this->sprite.getPosition();
}

void Player::collision(sf::RectangleShape& shape, const float& dt)
{
	if (this->sprite.getGlobalBounds().intersects(shape.getGlobalBounds()))
	{
		this->sprite.move(-this->movement);
		this->ifCollision = true;
	}
	else this->ifCollision = false;
}

void Player::saveToFile()
{
	std::ofstream file("save.txt");

	for (int i = 1; i <= 6; i++)
	{
		file << getStats(i) << "\n";
	}
	file << this->sprite.getPosition().x << " " << this->sprite.getPosition().y << "\n";
	if (tempSword)
		file << "1";
	else file << "0";
	file.close();
}

void Player::loadFromFile()
{
	std::ifstream file("save.txt");
	unsigned int temp[6];
	float a, b;
	bool sword;
	for (int i = 0; i <= 5; i++)
	{
		file >> temp[i];
	}
	file >> a >> b;

	setStats(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);
	this->sprite.setPosition({ a, b });
	file >> sword;
	if (sword)
	{
		if (!this->texture.loadFromFile("graphics/sheet_s.png"))
			throw("TEXTURES ERROR");
		this->sprite.setTexture(this->texture);
	}
	file.close();
}

const int Player::getImage()
{
	return this->animation->getCurrentImage();
}


const int Player::getStats(const int stat)
{
	if (stat == 1) return this->hp;
	else if (stat == 2) return this->strength;
	else if (stat == 3) return this->dexterity;
	else if (stat == 4) return this->money;
	else if (stat == 5) return this->dmg;
	else if (stat == 6) return this->lvl;
	else return -1;
}

void Player::update(const float& dt)
{
	this->movement.x = 0.f;
	this->movement.y = 0.f;
	this->sprite.setTexture(this->texture);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= movementSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += movementSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= movementSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += movementSpeed * dt;
	

	if (movement.x == 0.f && movement.y == 0.f)
	{
		row = 0;
	}
	else if (movement.x != 0.f)
	{
		row = 1;
		if (movement.x > 0.f)
			faceRight = true;
		else
			faceRight = false;

	}
	else if (movement.y != 0.f)
		row = 1;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		row = 2;   
		this->ifAttack = true;
	}
	else this->ifAttack = false;

	//picking sword
	if (ifSwordP)
	{
		if (!this->texture.loadFromFile("graphics/sheet_s.png"))
			throw("TEXTURES ERROR");
		this->sprite.setTexture(this->texture);
		tempSword = true;
	}
	ifSwordP = false;

	this->animation->update(row, dt, faceRight);
	
	this->sprite.setTextureRect(animation->uvRect);
	this->sprite.move(movement);



	//this->body.setSize({ static_cast<float>(this->texture.getSize().x), static_cast<float>(this->texture.getSize().y )});
	//this->body.setPosition(this->sprite.getPosition());
	
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Player::ifDead()
{
	if (this->getStats(1) <= 0)
	{
		std::cout << "YOU ARE DEAD\n";
	}
}

void Player::setStats(int hp, 
	unsigned int strength, unsigned int dexterity, 
	unsigned int money, unsigned int dmg, unsigned int lvl)
{
	this->hp = hp;
	this->strength = strength;
	this->dexterity = dexterity;
	this->money = money;
	this->dmg = dmg;
	this->lvl = lvl;
}
