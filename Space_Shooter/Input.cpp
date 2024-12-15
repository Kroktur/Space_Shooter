#include "Input.h"


PlayerInput::PlayerInput(IGameObject& object): m_object(object)
{
}

void PlayerInput::processinput( sf::Event& event)
{
	auto& objectship = dynamic_cast<Ship&>(m_object);
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







IaInput::IaInput(IGameObject& object) : m_actioncout(0), m_velocity(2.5f), m_random_number(0), m_object(object)
{
}

void IaInput::processinput( sf::Event& event) 
{
	auto& objectenemie = dynamic_cast<EnemieShip&>(m_object);
	auto& m_ennemie = objectenemie.m_ennemie;
	objectenemie.m_elapsedTime = objectenemie.m_clock.getElapsedTime();
	auto remainingDistance = 0;
	
	if (m_actioncout == 500)
		m_actioncout = 0;
	if (m_actioncout == 0)
	 m_random_number = objectenemie.m_rand->getrandomnumber(0, 6);

	auto m_magnetude = sqrt((objectenemie.m_delta.x) * (objectenemie.m_delta.x) + (objectenemie.m_delta.y) * (objectenemie.m_delta.y));
	srand(time(0));

	switch (m_random_number)
	{
	case Move_Right:
		if ((m_ennemie.getPosition().x + m_ennemie.getRadius()) < objectenemie.m_game.getWindowSize().x)
		{
			if (remainingDistance = objectenemie.m_game.getWindowSize().x - (m_ennemie.getPosition().x + m_ennemie.getRadius()) < m_velocity)
				objectenemie.m_position.x = remainingDistance;
			else
				objectenemie.m_position.x = m_velocity;
		}
		m_actioncout++;
		break;
	case Move_Left:
		if ((m_ennemie.getPosition().x - m_ennemie.getRadius()) > 0)
		{
			if (remainingDistance = m_ennemie.getPosition().x - m_ennemie.getRadius() < m_velocity)
				objectenemie.m_position.x = -remainingDistance;
			else
				objectenemie.m_position.x = -m_velocity;
		}
		m_actioncout++;
		break;
	case Move_Down:
		if ((m_ennemie.getPosition().y + m_ennemie.getRadius()) < objectenemie.m_game.getWindowSize().y)
		{
			if (remainingDistance = objectenemie.m_game.getWindowSize().y - (m_ennemie.getPosition().y + m_ennemie.getRadius()) < m_velocity)
				objectenemie.m_position.y = remainingDistance;
			else
				objectenemie.m_position.y = m_velocity;

		}
		m_actioncout++;
		break;
	case Move_Up:
		if ((m_ennemie.getPosition().y - m_ennemie.getRadius()) > 0)
		{
			if (remainingDistance = m_ennemie.getPosition().y - m_ennemie.getRadius() < m_velocity)
				objectenemie.m_position.y = -remainingDistance;
			else
				objectenemie.m_position.y = -m_velocity;
		}
		m_actioncout++;
		break;
	case Move_Closer_Player:
		
		objectenemie.m_position.x = objectenemie.m_delta.x / m_magnetude;
		objectenemie.m_position.y = objectenemie.m_delta.y / m_magnetude;
		m_actioncout++;
		break;
	case Shoot:
		if (objectenemie.m_elapsedTime.asSeconds() >= objectenemie.m_firerate)
		{
			objectenemie.m_fire = true;
			objectenemie.m_clock.restart();
		}
		m_actioncout++;
		break;
	case Do_Nothing:
		m_actioncout++;
		break;
	default:
		break;
	}




}

GameInput::GameInput(Game& game): m_game(game) ,m_lag(0.25)
{
}

void GameInput::processinput( sf::Event& event)
{
	m_Time = m_clock.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_Time.asSeconds() >= m_lag)
		{
			m_game.m_showAABB = !m_game.m_showAABB;
			m_clock.restart();
		}
	}
	
}