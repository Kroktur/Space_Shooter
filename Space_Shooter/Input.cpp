#include "Input.h"


void PlayerInput::processinput(sf::CircleShape& circle, sf::Event& event)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (m_ship.getPosition().x +m_ship.getRadius()) < m_game.getWindowSize().x )
	//	m_position.x = 5.f;	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& (m_ship.getPosition().x - m_ship.getRadius()) > 0)
	//	 m_position.x = -5.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_ship.getPosition().y + m_ship.getRadius()) < m_game.getWindowSize().y)
	//	m_position.y = 5.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (m_ship.getPosition().y - m_ship.getRadius()) > 0)
	//	m_position.y = -5.f;
}

void PlayerInput::processinput(sf::RectangleShape& rectangle, sf::Event& event)
{

}

void IaInput::processinput(sf::CircleShape& circle, sf::Event& event)
{
	
}

void IaInput::processinput(sf::RectangleShape& rectangle, sf::Event& event)
{

}
