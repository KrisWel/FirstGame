#include "player.h"
//Stale do ustawienia pozycji weapon wzgledem player
const float sword_range_x = 65.0f;
const float sword_range_y = 40.0f;

//***********KONSTRUKTOR I METODY WEAPON******************
Weapon::Weapon()
{
	mass.setSize({ 60, 60 });
	texture.loadFromFile("img/miecz.png");
	mass.setTexture(&texture);
}
void Weapon::Draw(sf::RenderWindow& window) { window.draw(mass); }
void Weapon::SetPosit(sf::Vector2f posit) { mass.setPosition(posit); }
//Metoda tworzy odbicie lustrzane klasy weapon
void Weapon::scale(float a, sf::Vector2f b)
{
	mass.setScale({ a, 1.0f });
	mass.setPosition(b);
}

//**************KONSTRUKTOR I METODY PLAYER*************888
player::player(int nr, sf::Vector2f size, sf::Vector2f posit)
{
	body.setSize(size);
	body.setPosition(posit);
	weapon.SetPosit({ posit.x+ sword_range_x, posit.y+ sword_range_y }); //ustala pozycje weapon wzgledem player'a
	if (nr == 1)
	{
		texture.loadFromFile("img/bezi.PNG");
		body.setTexture(&texture);
	}
	else if (nr == 2)
	{
		texture.loadFromFile("img/diego.PNG");
		body.setTexture(&texture);
	}
	else if (nr == 3)
	{
		texture.loadFromFile("img/ork.PNG");
		body.setTexture(&texture);
	}
}

void player::Draw(sf::RenderWindow& window) { window.draw(body);  weapon.Draw(window); }

void player::moving(float deltatime)
{
	//totaltime - czas jaki jest potrzebny do przesuniecia i odbicia player'a
	//potrzebne przez bug ktory pojawia sie przy zbyt szybkim klikanie A i D
	totaltime += deltatime; //deltatime z glownego programu - liczy czas poprzez clock
	body_posit = body.getPosition();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (totaltime >= 0.01f) //jezeli czas w glownej petli jest wiekaszy od 0.01s
		{
			if (right == true) //jezeli player skierowany jest w prawo
			{
				body.setScale({ -1.0f, 1.0f });
				body.setPosition(body_posit.x + 120.5f, body_posit.y);
				right = false;
			}
			body.move(-10.0f, 0);
			//zmienia pozycje miecza wzgledem kierunku postaci
			weapon.scale(-1.0f, { body.getPosition().x - sword_range_x, body.getPosition().y + sword_range_y });
			totaltime = 0.0f; // reset zegara
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (totaltime >= 0.01f) //jezeli czas w glownej petli jest wiekaszy od 0.01s
		{
			if (right == false) //jezeli player skierowany jest w lewo
			{
				body.setScale({ 1.0f, 1.0f });
				body.setPosition(body_posit.x - 120.5f, body_posit.y);
				right = true;
			}
			body.move(10.0f, 0);
			//zmienia pozycje miecza wzgledem kierunku postaci
			weapon.scale(1.0f, { body.getPosition().x + sword_range_x, body.getPosition().y + sword_range_y });
			totaltime = 0.0f; //reset zegara
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		body.move(0, 10.0f);
		//zmienia pozycje weapon wzgledem kierunki player
		//bez uwzglednienia miecz lata gdy klika sie S
		if (right == false) {
			weapon.SetPosit({ body.getPosition().x - sword_range_x, body.getPosition().y + sword_range_y });
		}
		else {
			weapon.SetPosit({ body.getPosition().x + sword_range_x, body.getPosition().y + sword_range_y });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		body.move(0, -10.0f);
		//zmienia pozycje weapon wzgledem kierunki player
		//bez uwzglednienia miecz lata gdy klika sie d
		if (right == false) {
			weapon.SetPosit({ body.getPosition().x - sword_range_x, body.getPosition().y + sword_range_y });
		}
		else {
			weapon.SetPosit({ body.getPosition().x + sword_range_x, body.getPosition().y + sword_range_y });
		}
	}
}