#include "playableGameObject.h"
#include "Input.h"

Ship::Ship(Game& game) : m_ship(50), m_angle(0), m_game(game)
{
	
	setShip();
}

void Ship::setShip()
{
	//set texture
	m_game.gettexture().getTexture("resource\\space_cat_.png");
	//set Ship position and Origin
	m_ship.setOrigin(m_ship.getRadius(), m_ship.getRadius());
	m_ship.setPosition(m_game.getWindowSize().x / 2, m_game.getWindowSize().y / 2);
	//input
	
}

void Ship::input(sf::Event event)
{
	
	resetmooveposition();
	
	PlayerInput input;
	input.processinput(*this, event);
}

void Ship::update(float deltatime)
{
	
}

void Ship::render()
{
}



void Ship::resetmooveposition()
{
	m_position.x = 0;
	m_position.y = 0;

}

void EnemieShip::input(sf::Event event)
{
}

void EnemieShip::update(float deltatime)
{
}

void EnemieShip::render()
{
}
