#include "GameObject.h"
#include "Game.h"
#include <cmath>



Ship::Ship(Game& game) : m_ship(50), m_angle(0), m_game(game) , firerate(0.25f)
{
	
	m_ship.setOrigin(m_ship.getRadius(), m_ship.getRadius());
	m_ship.setPosition(game.getWindowSize().x/2,game.getWindowSize().y/2);
	m_ship.setTexture(&game.gettexture().getTexture("resource\\space_cat_.png"));
	m_position.x = 0.f;
	m_position.y = 0.f;
	
}

Ship::~Ship()
{
	for (auto weaponidx : m_allWeapon)
	{
		delete weaponidx;
	}
	m_allWeapon.clear();
}

void Ship::HandleInput()
{
	m_position.x = 0;
	m_position.y = 0;
	elapsedTime = clock.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (m_ship.getPosition().x +m_ship.getRadius()) < m_game.getWindowSize().x )
		m_position.x = 5.f;	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& (m_ship.getPosition().x - m_ship.getRadius()) > 0)
		 m_position.x = -5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_ship.getPosition().y + m_ship.getRadius()) < m_game.getWindowSize().y)
		m_position.y = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (m_ship.getPosition().y - m_ship.getRadius()) > 0)
		m_position.y = -5.f;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (elapsedTime.asSeconds() >= firerate)
		{
			fire = true;
			
			clock.restart();
		}
		
	}
	
	m_angle = anglecalcul();
	
}

void Ship::Update()
{
	m_ship.move(m_position.x, m_position.y);
	m_ship.setRotation(m_angle);
	if (fire == true)
	{
		fire = false;
		Fire();
		 
	}
	
	for (auto idx = 0; idx < m_allWeapon.size(); ++idx)
	{
		m_allWeapon[idx]->Update();
		if (m_allWeapon[idx]->getPosition().x + m_allWeapon[idx]->getRadius() < 0 || m_allWeapon[idx]->getPosition().y + m_allWeapon[idx]->getRadius() < 0 || m_allWeapon[idx]->getPosition().x - m_allWeapon[idx]->getRadius() > 1920 || m_allWeapon[idx]->getPosition().y - m_allWeapon[idx]->getRadius() > 1080)
		{
			delete m_allWeapon[idx];
			m_allWeapon.erase(m_allWeapon.begin() + idx);
		}
	}
	

	
}

void Ship::Fire()
{
	IWeapon* missile = new Missile(m_ship, m_game);
	m_allWeapon.push_back(missile);

}

void Ship::Render(sf::RenderWindow& window)
{
	for (auto weaponidx : m_allWeapon)
	{
		weaponidx->Render(window);
	}	
	window.draw(m_ship);
}

float Ship::anglecalcul()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_game.getWindow());
	sf::Vector2f shipPos = m_ship.getPosition();
	float deltaX = mousePos.x - shipPos.x;
	float deltaY = mousePos.y - shipPos.y;
	float angle_ = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
	return angle_;
}

sf::CircleShape& Ship::getShape()
{
	return m_ship;
}

void Ship::boundingBoxS()
{
	float aminx = m_ship.getPosition().x - m_ship.getRadius() / 2;
	float aminy = m_ship.getPosition().y - m_ship.getRadius() / 2;
	float amaxx = m_ship.getPosition().x + m_ship.getRadius() / 2;
	float amaxy = m_ship.getPosition().y + m_ship.getRadius() / 2;
	AABB bbs = { { aminx,aminy }, { amaxx, amaxy } };
}

Ennemie_Ship::Ennemie_Ship(Game& game,sf::CircleShape& shape ) :m_enemie(50), m_angle(0), m_game(game) , m_ship(shape), velocity(1.5f) , firerate(1.f)
{
	m_enemie.setOrigin(m_enemie.getRadius(), m_enemie.getRadius());
	m_enemie.setPosition(SetPosition());
	m_enemie.setTexture(&game.gettexture().getTexture("resource\\space_cat_enemie.png"));
	m_position.x = 0.f;
	m_position.y = 0.f;
	m_magnetude = 0.f;
}

Ennemie_Ship::~Ennemie_Ship()
{
	for (auto weaponidx : m_allWeapon)
	{
		delete weaponidx;
	}
	m_allWeapon.clear();
}

void Ennemie_Ship::HandleInput()
{
	deltacalcul();
	anglecalcul();
	elapsedTime = clock.getElapsedTime();
	if (actioncout == 20)
	{
		actioncout = 0;
	}
	if (actioncout == 0)
	{
		m_position.x = 0;
		m_position.y = 0;
		random_number = rand->getrandomnumber(0, 5);
	}
	
	auto remainingDistance = 0;

	
	srand(time(0));
		
		switch (random_number)
		{
		case 0:
			if ((m_enemie.getPosition().x + m_enemie.getRadius()) < m_game.getWindowSize().x)
			{
				if (remainingDistance = m_game.getWindowSize().x - (m_enemie.getPosition().x + m_enemie.getRadius()) < velocity)
					m_position.x = remainingDistance;
				else
					m_position.x = velocity;
			}
			actioncout++;
			break;
		case 1:
			if ((m_enemie.getPosition().x - m_enemie.getRadius()) > 0)
			{
				if (remainingDistance = m_enemie.getPosition().x - m_enemie.getRadius() < velocity)
					m_position.x = -remainingDistance;
				else
					m_position.x = -velocity;
			}
			actioncout++;
			break;
		case 2:
			if ((m_enemie.getPosition().y + m_enemie.getRadius()) < m_game.getWindowSize().y)
			{
				if (remainingDistance = m_game.getWindowSize().y - (m_enemie.getPosition().y + m_enemie.getRadius()) < velocity)
					m_position.y = remainingDistance;
				else
					m_position.y = velocity;

			}
			actioncout++;
			break;
		case 3:
			if ((m_enemie.getPosition().y - m_enemie.getRadius()) > 0)
			{
				if (remainingDistance = m_enemie.getPosition().y - m_enemie.getRadius() < velocity)
					m_position.y = -remainingDistance;
				else
					m_position.y = -velocity;
			}
			actioncout++;
			break;
		case 4:
			Getcloserfromship();
			actioncout++;
			break;
		case 5:
			if (elapsedTime.asSeconds() >= firerate)
			{
			Fire();
			clock.restart();
			}
			actioncout++;
			break;
		default:
			actioncout++;
			break;
		}


	
}

void Ennemie_Ship::Update()
{
	for (auto idx = 0; idx < m_allWeapon.size(); ++idx)
	{
		m_allWeapon[idx]->Update();
		if (m_allWeapon[idx]->getPosition().x + m_allWeapon[idx]->getRadius() < 0 
			|| m_allWeapon[idx]->getPosition().y + m_allWeapon[idx]->getRadius() < 0 
			|| m_allWeapon[idx]->getPosition().x - m_allWeapon[idx]->getRadius() > 1920 
			|| m_allWeapon[idx]->getPosition().y - m_allWeapon[idx]->getRadius() > 1080)
		{
			delete m_allWeapon[idx];
			m_allWeapon.erase(m_allWeapon.begin() + idx);
		}
	}
	m_enemie.move(m_position.x, m_position.y);
	
	m_enemie.setRotation(m_angle);
}

void Ennemie_Ship::Fire()
{
	IWeapon* missile = new EnnemieMissile(m_enemie, m_game);
	m_allWeapon.push_back(missile);
}

void Ennemie_Ship::Render(sf::RenderWindow& window)
{
	for (auto weaponidx : m_allWeapon)
	{
		weaponidx->Render(window);
	}
	window.draw(m_enemie);
}

void Ennemie_Ship::anglecalcul()
{

	float angle = atan2(delta.y, delta.x);
	m_angle = angle * 180.0f / 3.1415926f;

}

void Ennemie_Ship::deltacalcul()
{
	delta.x = m_ship.getPosition().x - m_enemie.getPosition().x;
	delta.y = m_ship.getPosition().y - m_enemie.getPosition().y;
}

sf::Vector2f Ennemie_Ship::SetPosition()
{
	srand(time(0));
	sf::Vector2f position;
	int min_x = m_enemie.getRadius();
	int max_x = m_game.getWindowSize().x - m_enemie.getRadius();
	int min_y = m_enemie.getRadius();
	int max_y = m_game.getWindowSize().y - m_enemie.getRadius();
	int min = 0;
	int max = 3;
	int random_border = rand->getrandomnumber(min, max);
	int rabdom_Window_x = rand->getrandomnumber(min_x, max_x);
	int rabdom_Window_y = rand->getrandomnumber(min_y, max_y);
	switch (random_border)
	{
	case 0:
		position.x = min_x;
		position.y = rabdom_Window_y;
		return position; 
		break;
	case 1 :
		position.x = rabdom_Window_x;
		position.y = min_y;
		return position;
		break;
	case 2:
		position.x = max_x;
		position.y = rabdom_Window_y;
		return position;
		break;
	case 3:
		position.x = rabdom_Window_x;
		position.y = max_y;
		return position;
		break;
	default:
		break;
	}

}

void Ennemie_Ship::Getcloserfromship()
{
	SetMagnetude();
	m_position.x = delta.x / m_magnetude;
	m_position.y = delta.y / m_magnetude;
	m_enemie.move( velocity * m_position.x, velocity * m_position.y);
}

void Ennemie_Ship::SetMagnetude()
{
	m_magnetude = sqrt((delta.x) * (delta.x) + (delta.y) * (delta.y));	
}


sf::CircleShape& Ennemie_Ship::getShape()
{
	return m_enemie;
}

void Ennemie_Ship::boundingBoxE()
{

	float aminx = m_enemie.getPosition().x - m_enemie.getRadius() / 2;
	float aminy = m_enemie.getPosition().y - m_enemie.getRadius() / 2;
	float amaxx = m_enemie.getPosition().x + m_enemie.getRadius() / 2;
	float amaxy = m_enemie.getPosition().y + m_enemie.getRadius() / 2;
	AABB bbe = { { aminx,aminy }, { amaxx, amaxy } };
};

