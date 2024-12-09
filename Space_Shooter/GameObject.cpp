#include "GameObject.h"
#include "Game.h"


Ship::Ship(Game& game) : m_ship(50) , m_angle(0) ,m_game(game)
{
	
	m_ship.setOrigin(m_ship.getRadius(), m_ship.getRadius());
	m_ship.setPosition(game.getWindowSize().x/2,game.getWindowSize().y/2);
	m_ship.setTexture(&game.gettexture().getTexture("resource\\space_cat_.png"));
	m_positionrate.x = 0.f;
	m_positionrate.y = 0.f;
	
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
	m_positionrate.x = 0;
	m_positionrate.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (m_ship.getPosition().x +m_ship.getRadius()) < m_game.getWindowSize().x )
		m_positionrate.x = 5.f;	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& (m_ship.getPosition().x - m_ship.getRadius()) > 0)
		 m_positionrate.x = -5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_ship.getPosition().y + m_ship.getRadius()) < m_game.getWindowSize().y)
		m_positionrate.y = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (m_ship.getPosition().y - m_ship.getRadius()) > 0)
		m_positionrate.y = -5.f;

	
	m_angle = anglecalcul();
	
}

void Ship::Update()
{
	
	for (auto idx = 0; idx < m_allWeapon.size(); ++idx)
	{
		m_allWeapon[idx]->Update();
		if (m_allWeapon[idx]->getPosition().x + m_allWeapon[idx]->getRadius() < 0 || m_allWeapon[idx]->getPosition().y + m_allWeapon[idx]->getRadius() < 0 || m_allWeapon[idx]->getPosition().x - m_allWeapon[idx]->getRadius() > 1920 || m_allWeapon[idx]->getPosition().y - m_allWeapon[idx]->getRadius() > 1080)
		{
			delete m_allWeapon[idx];
			m_allWeapon.erase(m_allWeapon.begin() + idx);
		}
	}
	
	m_ship.move(m_positionrate.x, m_positionrate.y);
	m_ship.setRotation(m_angle);
	
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

