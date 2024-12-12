#include "Input.h"


void PlayerInput::processinput(IGameObject& object, sf::Event& event)
{
	/*auto &objectship = dynamic_cast<Ship&>(object);
	auto &m_ship = objectship.m_ship;
	auto windowsize = objectship.m_game.getWindowSize();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (m_ship.getPosition().x + m_ship.getRadius()) < windowsize.x)
		objectship.m_position.x = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& (m_ship.getPosition().x - m_ship.getRadius()) > 0)
		objectship.m_position.x = -5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_ship.getPosition().y + m_ship.getRadius()) < windowsize.y)
		objectship.m_position.y = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (m_ship.getPosition().y - m_ship.getRadius()) > 0)
		objectship.m_position.y = -5.f;*/
}



void IaInput::processinput(IGameObject& object, sf::Event& event)
{
	
}


