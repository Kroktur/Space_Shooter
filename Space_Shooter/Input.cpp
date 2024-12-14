#include "Input.h"


void PlayerInput::processinput(IGameObject& object, sf::Event& event)
{
	auto& objectship = dynamic_cast<Ship&>(object);
	auto& m_ship = objectship.m_ship;
	auto windowsize = objectship.m_game.getWindowSize();
	objectship.m_elapsedTime = objectship.m_clock.getElapsedTime();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (objectship.m_elapsedTime.asSeconds() >= objectship.m_firerate)
		{
			objectship.m_fire = true;
			objectship.m_clock.restart();
		}

	}
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (m_ship.getPosition().x + m_ship.getRadius()) < windowsize.x)
	
		objectship.m_position.x = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& (m_ship.getPosition().x - m_ship.getRadius()) > 0)
	
		objectship.m_position.x = -5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_ship.getPosition().y + m_ship.getRadius()) < windowsize.y)

		objectship.m_position.y = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (m_ship.getPosition().y - m_ship.getRadius()) > 0)
	
		objectship.m_position.y = -5.f;
}






IaInput::IaInput() : m_actioncout(0), m_velocity(2.5f), m_random_number(0)
{
}

void IaInput::processinput(IGameObject& object, sf::Event& event) 
{
	auto& objectenemie = dynamic_cast<EnemieShip&>(object);
	auto& m_ennemie = objectenemie.m_ennemie;
	objectenemie.m_elapsedTime = objectenemie.m_clock.getElapsedTime();
	auto remainingDistance = 0;
	
	if (m_actioncout == 500)
		m_actioncout = 0;
	if (m_actioncout == 0)
	 m_random_number = objectenemie.m_rand->getrandomnumber(0, 5);

	auto m_magnetude = sqrt((objectenemie.m_delta.x) * (objectenemie.m_delta.x) + (objectenemie.m_delta.y) * (objectenemie.m_delta.y));
	srand(time(0));

	switch (m_random_number)
	{
	case 0:
		if ((m_ennemie.getPosition().x + m_ennemie.getRadius()) < objectenemie.m_game.getWindowSize().x)
		{
			if (remainingDistance = objectenemie.m_game.getWindowSize().x - (m_ennemie.getPosition().x + m_ennemie.getRadius()) < m_velocity)
				objectenemie.m_position.x = remainingDistance;
			else
				objectenemie.m_position.x = m_velocity;
		}
		m_actioncout++;
		break;
	case 1:
		if ((m_ennemie.getPosition().x - m_ennemie.getRadius()) > 0)
		{
			if (remainingDistance = m_ennemie.getPosition().x - m_ennemie.getRadius() < m_velocity)
				objectenemie.m_position.x = -remainingDistance;
			else
				objectenemie.m_position.x = -m_velocity;
		}
		m_actioncout++;
		break;
	case 2:
		if ((m_ennemie.getPosition().y + m_ennemie.getRadius()) < objectenemie.m_game.getWindowSize().y)
		{
			if (remainingDistance = objectenemie.m_game.getWindowSize().y - (m_ennemie.getPosition().y + m_ennemie.getRadius()) < m_velocity)
				objectenemie.m_position.y = remainingDistance;
			else
				objectenemie.m_position.y = m_velocity;

		}
		m_actioncout++;
		break;
	case 3:
		if ((m_ennemie.getPosition().y - m_ennemie.getRadius()) > 0)
		{
			if (remainingDistance = m_ennemie.getPosition().y - m_ennemie.getRadius() < m_velocity)
				objectenemie.m_position.y = -remainingDistance;
			else
				objectenemie.m_position.y = -m_velocity;
		}
		m_actioncout++;
		break;
	case 4:
		
		objectenemie.m_position.x = objectenemie.m_delta.x / m_magnetude;
		objectenemie.m_position.y = objectenemie.m_delta.y / m_magnetude;
		m_actioncout++;
		break;
	case 5:
		if (objectenemie.m_elapsedTime.asSeconds() >= objectenemie.m_firerate)
		{
			objectenemie.m_fire = true;
			objectenemie.m_clock.restart();
		}
		m_actioncout++;
		break;
	default:
		m_actioncout++;
		break;
	}




}


