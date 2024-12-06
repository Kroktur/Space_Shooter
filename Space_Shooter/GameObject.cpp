#include "GameObject.h"
#include "Game.h"



Ship::Ship(Game& game) : m_ship(50) , m_angle(0)
{
	m_ship.setOrigin(m_ship.getRadius(), m_ship.getRadius());
	m_ship.setPosition(game.getWindowSize().x/2,game.getWindowSize().y/2);
	m_ship.setTexture(&game.gettexture().getTexture("C:\\Users\\ablanchet\\source\\repos\\Space_Shootertest3\\Space_Shooter\\resource\\space_cat_.png"));
	m_positionrate.x = 0.f;
	m_positionrate.y = 0.f;
	
}

void Ship::HandleInput()
{
	m_positionrate.x = 0;
	m_positionrate.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_positionrate.x = 10.f;	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))	
		 m_positionrate.x = -10.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_positionrate.y = 10.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		m_positionrate.y = -10.f;

	
	m_angle = anglecalcul();
	
}

void Ship::Update()
{
	m_ship.move(m_positionrate.x, m_positionrate.y);
	m_ship.setRotation(m_angle);
	
}

void Ship::Render(sf::RenderWindow& window)
{
	
	window.draw(m_ship);
	
	
	
}

float Ship::anglecalcul()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	sf::Vector2f shipPos = m_ship.getPosition();
	float deltaX = mousePos.x - shipPos.x;
	float deltaY = mousePos.y - shipPos.y;
	float angle_ = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
	return angle_;
}
